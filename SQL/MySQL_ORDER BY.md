[toc]

# ORDER BY 排序原理

-------------------

## 1. 全字段排序

我们经常会有根据指定的字段排序显示结果的需求，那么 `MySQL` 排序用到的是 `order by` 指令。
例如以下场景：有一个表 `t`，需要根据指定的城市查询所有人名字，并按名字排序返回结果。

```mysql

CREATE TABLE `t` (
  `id` int(11) NOT NULL,
  `city` varchar(16) NOT NULL,
  `name` varchar(16) NOT NULL,
  `age` int(11) NOT NULL,
  `addr` varchar(128) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `city` (`city`)
) ENGINE=InnoDB;
```

 此时，`SQL` 语句的写法：`select city, name, age from t where city = "杭州" order by name limit 1000;`  

为了避免全表扫描，我们在字段 `city` 上加索引。执行 `explain` 命令，显示上述命令的执行过程：
![](.\pictures\order_by.png)

`Extra` 这个字段中的 `Using filesort` 表示的就是要排序，`MySQL` 会个每个线程分配一块内存用于排序，称为 `sort buffer`。

字段 `city` 上的索引：

![](E:\CS_NOTE_SELF\CS_NOTE\SQL\pictures\city_index.png)

那么，满足 `city = "杭州"` 的行，是从 `ID_X` 到 `ID_(X+N)` 的记录。
通常情况下，这个语句执行流程如下所示 ：

1.  初始化 `sort_buffer`，确定放入 `name、city、age` 这三个字段；

2.  从索引 `city` 找到第一个满足 `city='杭州'`条件的主键 `id`，也就是图中的 `ID_X`；

3.  到主键 `id` 索引取出整行，取 `name、city、age` 三个字段的值，存入 `sort_buffer` 中；

4.  从索引 `city` 取下一个记录的主键 `id`；重复步骤 3、4 直到 city 的值不满足查询条件为止，对应的主键 `id` 也就是图中的 `ID_Y`；

5.  对 `sort_buffer` 中的数据按照字段 `name` 做快速排序；

按照排序结果取前 1000 行返回给客户端。我们把这个排序过程，称为 **全字段排序** ，执行流程的示意图如下所示。
![](.\pictures\order_by1.png)

上图中 "按 `name` 排序" 这个动作，可能在内存中完成，也可能使用外部排序，这取决于排序所使用的内存和参数 `sort_buffer_size`。
`sort_buffer_size` 就是 `MySQL` 为排序开辟的内存 (`sort_buffer`) 的大小。如果要排序的数据量比 `sort_buffer_size` 小，那么排序就在内存中完成。否则， 如果数据量太大的话，那么不得不利用磁盘临时文件辅助排序。

