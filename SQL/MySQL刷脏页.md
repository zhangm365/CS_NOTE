[toc]

# MySQL 执行语句为什么突然变 "慢" 了？

-------------------

## 1 . MySQL 更新语句流程

`InnoDB` 在处理更新语句时，只做了写日志 `redo log` 这一操作，在更新完内存和写完 `redo log` 后，就返回给客户端，表示本次的更新操作完成。这个过程就是 `MySQL` 中的 `WAL` 技术，即 `Write-Ahead Logging` ，它的关键点是先写日志，再写磁盘，可以提高 `MySQL` 的读写性能。



当内存数据页和磁盘数据页内容不一致时，称此时的内存数据页为 "脏页"。

## 2 . 数据库 flush 的时机

### 2.1 `redo log` 日志已写满

这时系统会停掉所有更新操作，把 `checkpoint` 向前推进，`redo log` 留出空间继续写。
如下图所示：当 `write pos` 和 `checkpoint` 指向相同位置时，表明 `redo log` 已满，这时需要将 `redo log` 中的日志 `flush` 磁盘上。当 `checkpoint` 位置从 `cp` 推到 `cp'` 时，需要将这两个点之间的日志对应的脏页都 `flush` 到磁盘上。之后，`write pos` 到 `cp'` 之间就是可以继续写入 `redo log` 日志的区域了。 

![](.\pictures\redo_log1.jpg)

### 2.2 系统内存不足

当内存不足时，就需要淘汰一些数据页，空出内存给新数据页使用。如果淘汰的是 "脏页"，就要将 "脏页" 刷到磁盘，变成 "干净页" 后复用。

### 2.3 MySQL 认为系统处于 "空闲" 状态

`MySQL` 会抽空刷新一些 "脏页"。

### 2.4 MySQL 正常关闭连接的时候

`MySQL` 会把内存的脏页全部 `flush` 磁盘上，保证下次启动 `MySQL` 的时候，所有数据是正确的。

## 3. InnoDB 刷脏页的控制策略

`InnoDB` 引擎必须知道所在主机的 `IO` 能力，这样 `InnoDB` 才可以知道需要全力刷脏页的时候，可以有多快。
参数 `innodb_io_capacity ` 可以告诉 `InnoDB` 引擎你的磁盘能力。但是磁盘能力不能只用来刷脏页，还需响应其他请求。所以 `InnoDB` 需要设计策略控制刷脏页的速度，因为如果刷页速度太慢，一是导致内存脏页太多，二是导致 `redo log` 写满。所以，主要考虑以下两个因素：

1.  内存脏页的比例；

    内存中的脏页比例是通过 `Innodb_buffer_pool_pages_dirty/Innodb_buffer_pool_pages_total` 来计算出的。

    ```mysql
    select VARIABLE_VALUE into @a from performance_schema.global_status where VARIABLE_NAME = 'Innodb_buffer_pool_pages_dirty'; 
    select VARIABLE_VALUE into @b from performance_schema.global_status where VARIABLE_NAME = 'Innodb_buffer_pool_pages_total'; 
    select @a/@b;
    ```

    

2.  `redo log` 写盘速度。

`InnoDB` 会根据这两个因素分别算出两个数字，取这两个数字的最大值 `R`，然后按照 `innodb_io_capacity` 定义的能力乘以 `R%` 来控制刷脏页的速度。

