[toc]

#  MySQL 幻读与锁

[MySQL 20 讲](https://time.geekbang.org/column/article/75173) 			[MySQL 21 讲](https://time.geekbang.org/column/article/75659)

-------

## 1. MySQL 幻读

### 1.1 幻读的定义

幻读指的是一个事务在前后两次查询同一范围的数据时，后一次查询看到了前一次查询没有看到的行。因此，幻读，指的是 "新插入的行"。
而行锁只能锁住行，但对于新插入的记录，要更新的是记录之间的 "间隙"。因此，为了解决 "幻读" 的问题，`InnoDB` 在 **可重复读** 隔离级别下引入了新的锁，即间隙锁（`Gap Lock`）。
如下是表结构：

```mysql
// 建表语句
CREATE TABLE `t_20` (
  `id` int(11) NOT NULL,
  `c` int(11) DEFAULT NULL,
  `d` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `c` (`c`)
) ENGINE=InnoDB;

insert into t values(0,0,0),(5,5,5),
(10,10,10),(15,15,15),(20,20,20),(25,25,25);
```

这个表 `t_20` 的有 6 个记录， 这就产生了 7 个间隙。如下：

![](E:\CS_NOTE_SELF\CS_NOTE\SQL\pictures\20_1.png)

因此，在执行 `select * from t_20 where d = 5 for update` 时，在全表扫描过程中，不仅给扫描行加上了行锁，同时在行之间的间隙加上了间隙锁。

### 1.2 间隙锁的冲突

间隙锁之间的冲突和行锁之间的冲突是不一样的。行锁之间的冲突关系是 "另一个行锁"。如下所示：行锁之间的冲突关系。

|     锁类型      | 读锁 | 写锁 |
| :-------------: | :--: | :--: |
| 读锁 ( `S` 锁 ) | 兼容 | 冲突 |
| 写锁 ( `X` 锁 ) | 冲突 | 冲突 |

而 **间隙锁** 之间的冲突是在这个间隙间插入一条新纪录这个操作，间隙锁之间不存在冲突的。例如：`c = 7` 这行记录是不存在的，`session A` 加的是间隙锁 (5, 10)。 `session B` 这个操作也是在这个间隙加锁，但是不会被阻塞的。他们之间有共同的目标，即保护这个间隙，不允许插入新记录。但它们本身的加锁行为是不会互斥的，只有向他们共同保护的这个间隙插入记录时，才会发生冲突。

![](E:\CS_NOTE_SELF\CS_NOTE\SQL\pictures\20_2.png)



### 1.3 `Next-Key Lock`

`Next-Key Lock` 是由索引记录上的行锁和索引记录之前的间隙上的间隙锁组成。因此， `Next-Key Lock` 都是「前闭后开」区间的结构。

## 2. `Next-Key Lock` 加锁

### 2.1 加锁原则

1.  加锁的基本单位是： `Next-Key Lock`，即 「前闭后开」区间；
2.  查找数据过程中访问到的索引才会加锁。

这些锁是在执行语句过程中一个一个加的，所以加锁是一个动态过程。

### 2.2 优化原则

基于上述的加锁规则，`MySQL` 为了提高事务并发度，对 `Next-Key Lock` 锁进行了一定的优化。优化原则如下：

1.  在**唯一索引**上进行等值查询时，加锁类型由 `Next-Key Lock` 退化为行锁；

2.  在索引上等值查询时，向右遍历时且最后一个值不满足等值条件时， `Next-Key Lock` 退化为间隙锁。

### 2.3 锁日志记录

`lock_mode X waiting` 表示`next-key lock`；
`lock_mode X locks rec but not gap`是只有行锁；
`locks gap before rec`，就是只有间隙锁；
