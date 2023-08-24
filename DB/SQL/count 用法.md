# count 原理

- [count 原理](#count-原理)
  - [1. count 用法](#1-count-用法)
    - [1.1 count(\*)](#11-count)
      - [a. 实现方式](#a-实现方式)
      - [b. 为什么 `InnoDB` 引擎不像 `MyISAM` 一样，也把表的总行数存起来？](#b-为什么-innodb-引擎不像-myisam-一样也把表的总行数存起来)
    - [1.2 count(column)](#12-countcolumn)
    - [1.3 count(常量)](#13-count常量)
    - [1.4  三种用法的性能](#14--三种用法的性能)
  - [2. InnoDB 对 count(\*) 的优化](#2-innodb-对-count-的优化)

## 1. count 用法

`count()` 函数是 `MySQL/PostgreSQL` 中的一个聚合函数，用来统计数据表中的行数或符合特定条件的行数。
  
  ```sql
  -- 统计数据表中的所有行数 
  SELECT 
    COUNT(*) 
  FROM 
    table_name
  WHERE
    condition;
  ```

### 1.1 count(*)

用来统计数据表中的所有行数，可能包含 `NULL` 和重复值。

#### a. 实现方式

在不同的 `MySQL` 引擎中，`count(*)` 有不同的实现方式。

- `MyISAM` 引擎将表的总行数存在了磁盘上，因此，执行 `count(*)` 会直接返回结果，效率较高；
- `InnoDB` 引擎在执行 `count(*)` 时，会将表中的记录一行一行从引擎中读出来，然后累积计数，即要全表扫描，故效率较低。

而 `PostgreSQL` 也将进行全盘扫描，因为基于 `MVCC` 的机制，每个事务中读取的表状态可能不一致，所以 `PostgreSQL` 也不会缓存表的总行数。

#### b. 为什么 `InnoDB` 引擎不像 `MyISAM` 一样，也把表的总行数存起来？

`InnoDB` 是事务型引擎，默认隔离级别是可重复读，因为存在 `MVCC` ，所以 `InnoDB` 表 "应该返回多少行" 是不确定的。扫描每一行的记录都要判断是否对这个事务可见，因此，`InnoDB` 只能一行一行将记录读出判断，可见的行才能用于计算 "基于这个查询" 的表的总行数。

### 1.2 count(column)

统计特定列中具有值的行数，会忽略 `NULL` 值，但可能包括重复值。

  ```sql
  SELECT 
    COUNT(column) 
  FROM 
    table_name
  WHERE
    condition;
  ```

例如：对于 `count(主键 id)` 来说，`InnoDB` 引擎会遍历整张表，把每一行的 `id` 值都取出来，返回给 `server` 层。`server` 层拿到 `id` 后，判断是不可能为空的，就按行累加。

如下语句将只包括 `column` 列中不为 `NULL` 且具有唯一值的行数。

  ```sql
  SELECT 
    COUNT(DISTINCT(column)) 
  FROM 
    table_name
  WHERE
    condition;
  ```

### 1.3 count(常量)

用来统计数据表中的所有行数，返回结果同 `count(*)`。
如具体用法：`count(1)`。

### 1.4  三种用法的性能

`count(column) < count(1) ≈ count(*)`

建议使用 `count(*)` 语句来统计行数。

## 2. InnoDB 对 count(*) 的优化

`InnoDB` 针对 `count(*)` 进行了专门优化。即通过低成本的索引进行扫表，而不关注表的具体内容。
因为 `InnoDB` 索引分为主键索引和非主键索引，主键索引的叶子节点保存的是整行记录，而非主键索引的叶子节点保存的是主键值，所以，`MySQL` 会优先选择最小的索引树进行遍历，这样可以尽可能地减少扫描的数据量。
