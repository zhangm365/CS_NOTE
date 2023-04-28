- [1. join 基本用法](#1-join-基本用法)
  - [1.1 join 语法](#11-join-语法)
  - [1.2 straight_join 语法](#12-straight_join-语法)
  - [1.3 left join 语法](#13-left-join-语法)
- [2. join 的相关算法](#2-join-的相关算法)
  - [2.1 Index Nested-Loop Join](#21-index-nested-loop-join)
  - [2.2 Block Nested-Loop Join](#22-block-nested-loop-join)

## 1. join 基本用法

`join` 用在 `select` 语句中关联表，因此称为联结。下面是 `join` 语法的几种不同用法。

### 1.1 join 语法

语句联结中可以直接使用 `join` 语义，那么这个语句在执行过程中，优化器会根据表的结构进行优化指定驱动表和被驱动表。

### 1.2 straight_join 语法

`straight_join` 让`MySQL` 采用固定的联结方式，即严格指定其左边的表是驱动表，右边的表是被驱动表。如下语句：

```mysql
CREATE TABLE `t2` 
( `id` int(11) NOT NULL, 
 `a` int(11) DEFAULT NULL, 
 `b` int(11) DEFAULT NULL, 
 PRIMARY KEY (`id`), 
 KEY `a` (`a`)
)ENGINE=InnoDB;

create table t1 like t2;

select * from t1 straight_join t2 on (t1.a=t2.a); -- 表 t1 是驱动表，t2 是被驱动表。优化器不再优化联结顺序，按指定的方式 JOIN

```

### 1.3 left join 语法

在语句中使用了 `left join` 方式，大部分情况其左边的表是驱动表，右边的表是被驱动表。但是优化器可能会优化联结表的顺序，即其左边的表不一定是驱动表，要根据语句的实际执行情况分析。例如：在条件筛选时使用 **`where`** 语义，如下场景实验结果：

![](./pictures/34_2.png)

#### 1.3.1 left join 结果集

如下创建两个表，然后执行 `left join` 查询语句，如下：
从语句输出可以得知结果集中会包含在驱动表中而不在被驱动表中的数据，这些数据的输出为 `NULL`。

```mysql

create table t_44_a(f1 int, f2 int, index(f1))engine=innodb;
create table t_44_b(f1 int, f2 int)engine=innodb;
insert into t_44_a values(1,1),(2,2),(3,3),(4,4),(5,5),(6,6);
insert into t_44_b values(3,3),(4,4),(5,5),(6,6),(7,7),(8,8);

mysql> select * from t_44_a left join t_44_b on (t_44_a.f1 = t_44_b.f1) and (t_44_a.f2 = t_44_b.f2);
+------+------+------+------+
| f1   | f2   | f1   | f2   |
+------+------+------+------+
|    1 |    1 | NULL | NULL |
|    2 |    2 | NULL | NULL |
|    3 |    3 |    3 |    3 |
|    4 |    4 |    4 |    4 |
|    5 |    5 |    5 |    5 |
|    6 |    6 |    6 |    6 |
+------+------+------+------+
6 rows in set (0.02 sec)


```



## 2. join 的相关算法

`join` 语义在联结相关表时，根据表上索引的结构采用不同的算法。

### 2.1 Index Nested-Loop Join

这个算法是循环嵌套联结算法，简称 `NLJ` 算法。这个算法的使用场景是 **使用了被驱动表的索引**。
如上面的执行语句 `select * from t1 straight_join t2 on (t1.a=t2.a);`，在联结过程中使用了被驱动表 `t2` 上的索引 `a`，使用的是 `NLJ` 算法。 
如果一条 `join` 语句中 `explain` 命令的 `Extra` 字段什么都没显示的话，那这个 `join` 语句使用的是 `NLJ` 算法。

算法的执行流程如下：

1.  取表 `t1` 中的一行数据 `R`；
2.  从数据行 `R` 取出字段 `a`，然后和表 `t2` 中的 `a` 比较；
3.  取表 `t2` 中的满足条件的数据，和 `R` 组成一行，作为结果集的一部分；
4.  重复执行步骤 `1,2,3` 直到表 `t1` 的末尾循环结束。

因此，在这种场景中，小表适合做驱动表，然后使用被驱动表上的索引，语句的查询性能较高。

### 2.2 Block Nested-Loop Join ( hash join )

当被驱动表上没有索引时，`join` 联结过程中使用该算法，简称 `BNL` 算法。在 `MySQL 8.0` 版本之后，这个算法改为了 `hash join` 算法。
如下输出：(实验是建表 `t_34_1--->t1, t_34_2--->t2` 等)
用 `explain` 命令查看时，由于两个表的字段 `b` 都没有索引，联结表过程中使用了 `join buffer` 缓冲区，即使用 `hash join` 算法，如下的 `Extra` 字段所示。由于表 `t1` 的行数较少，所以优化器选择了 `t_34_1` 作为驱动表，`t_34_2` 为被驱动表。

![](./pictures/34_1.png)

 这个算法的流程如下：

1.  将驱动表的数据全部读入内存 `join buffer` 中，这里的 `join buffer` 是 **哈希表结构**；
2.  顺序遍历被驱动表中的所有行（全表扫描），每一行数据与 `join buffer` 中的数据使用哈希表进行等值匹配，匹配成功则作为结果集的一部分返回；

如果 `join buffer` 中无法一次性全部放入驱动表的数据，那采取分段的策略进行放置驱动表的数据。

 

