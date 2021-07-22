

[toc]

# MySQL 主备原理

[`MySQL实战24讲`](https://time.geekbang.org/column/article/76446)

--------------------------

`binlog` 日志文件可以用来主备同步。

## 1. MySQL 主备的基本原理

如下图所示，是 `MySQL` 的主备切换流程。在状态 `1` 中，客户端的读写都是直接访问节点 `A`，而节点 `B` 是 `A` 的备库，只是将 `A` 的更新同步过来，到本地执行。这样，保证节点 `A` 与 `B` 的数据是相同的。 之后，如果切换到状态 `2`，原理是相同的。需要注意的是，备库的节点通常设置为 **`readonly`** 状态。

![](.\pictures\binlog_1.png)

## 2. binlog 日志格式

`MySQL` 系统中的 `binlog` 日志有 `3` 种格式，分别是 `row`、`statement`、`mixed` 格式。

1.  `binlog_format` 来设置指定的日志格式。如：`set global binlog_format = statement`。`MySQL` 从版本 `5.7.7` 之后，二进制日志文件格式**默认为 `row` 格式**。
2.  `show variables like '%datadir%'`：显示二进制日志文件的存储位置。

### 2.1 相关命令

1.  `show variables like 'log_bin'`：查看服务器端 `binlog` 日志设置是否开启，选项为 `on/off`。启用二进制文件记录后，服务器会将所有更改数据的语句记录在二进制日志中，用于备份和复制。 默认是开启的。
2.  `show master status\G` ：显示当前正在写入 `binlog` 日志的文件。
3.  `show binary logs` ：显示 `MySQL` 中所有的二进制日志文件列表。
4.  `show binlog events` ：默认显示系统中第一个 `binlog` 日志内容。
5.  `show binlog events in 'binlog.000116'` ：显示指定的 `binlog.000116` 日志中的内容。

### 2.1 statement-based 格式

`statement`是基于原始`SQL`语句的日志格式。 
下图是显示格式为 `statement` 格式的二进制日志文件内容：

![](.\pictures\24_0.png)![](.\pictures\24_1.png)

从上图可以得知，`binlog` 日志记录了原始的 `SQL` 语句：`delete from t_24 where a >=4 and t_modified <= '2018-11-10' limit 1` 。
但是，`statement-based` 的二进制日志可能会导致主备库数据不一致。

### 2.2 row-based 格式

`row` 格式是基于表中哪个记录被修改的格式。
如下是这种格式的日志文件内容（ `insert` 操作 ）：

![](.\pictures\24_2.png)

可以看出，`row` 记录的不是原始的 `SQL` 语句，对应的语句替换成了两个事件类型：`Table_map` 和 `Write_rows` 。`Table_map`：表示操作的数据库 `sql_test` 中的表 `t_24`。而  `Write_rows`：用于定义写入的行为。

可以使用 `mysqlbinlog` 工具显示解析 `binlog` 文件中对应的内容。
`mysqlbinlog -vv /var/lib/mysql/binlog.000155 --start-position=3151`，如下：

![](E:\CS_NOTE_SELF\CS_NOTE\SQL\pictures\24_3.png) 

以下是 `update` 操作的 `row` 格式的日志文件内容：

![](.\pictures\24_4.png)

参数 `--start-position` 来指定从哪个位置解析日志文件。之前的图中显示，这个执行语句的 `binlog` 日志是从 `3151` 这个位置开始的。 
参数 `-vv` 具体显示解析的内容 ( `@1=4、@2=4` 这些值 )。
因此，从 `row-based` 格式的 `binlog` 文件中，可以看出 `binlog` 里记录的是真是改变行的主键 `id`。
**这样就可以保证主备库修改数据的一致性**。

### 2.3 mixed-based 格式

`statement-based` 的二进制日志占用空间小，而同样的 `row-based` 的二进制会占用更大空间，导致写 `binlog` 文件耗用更多的 `IO` 资源。因此，`mixed-based` 是一种折中方案，`MySQL` 会判断语句是否会引起主备不一致，如果有可能，则采用 `row` 格式，否则大多数情况下采用 `statement` 格式。