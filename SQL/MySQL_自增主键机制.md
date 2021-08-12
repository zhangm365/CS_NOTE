- [MySQL 自增主键机制](#mysql-自增主键机制)
  - [1. MySQL 自增主键修改](#1-mysql-自增主键修改)
    - [1.1 自增值修改机制](#11-自增值修改机制)
    - [1.2  自增值修改时机](#12--自增值修改时机)
  - [2. 自增主键不连续原因](#2-自增主键不连续原因)
    - [2.1 唯一键冲突](#21-唯一键冲突)
    - [2.2 事务回滚](#22-事务回滚)
    - [2.3 批量插入数据](#23-批量插入数据)
  - [3. 自增主键不回退的原因](#3-自增主键不回退的原因)
  - [4. 自增锁](#4-自增锁)

# MySQL 自增主键机制

## 1. MySQL 自增主键修改

自增主键可以让主键索引尽可能地保持递增顺序插入，使得索引更加紧凑，避免了页分裂。这样存储数据的效率更高。

### 1.1 自增值修改机制

在 `MySQ`L 里面，如果字段 `id` 被定义为 `AUTO_INCREMENT`，在插入一行数据的时候，自增值的行为如下：
	如果插入数据时 `id` 字段指定为 `0、null` 或未指定值，那么就把这个表当前的 `AUTO_INCREMENT` 值填到自增字段；
	如果插入数据时 `id` 字段指定了具体的值，就直接使用语句里指定的值。

### 1.2  自增值修改时机

自增主键的修改过程如下：

1.  假设表 `t_39` 里面已经有了 `(1,1,1)` 这条记录，这时再执行一条插入数据命令：`insert into t values(null, 1, 1);`
2.  这个语句的执行流程就是：执行器调用 `InnoDB` 引擎接口写入一行，传入的这一行的值是 `(0,1,1);`
3.  `InnoDB` 发现用户没有指定自增 `id` 的值，获取表 `t_39`当前的自增值 `2`，将传入的行的值改成 `(2,1,1);`
4.  将表的自增值改成 `3`；
5.  继续执行插入数据操作，由于已经存在 `c=1` 的记录，所以报 `Duplicate key error`，语句返回。

即使数据插入不成功，但是主键 `id` 不会回滚。

## 2. 自增主键不连续原因

### 2.1 唯一键冲突

唯一键冲突会导致自增主键不连续。如以下代码示例：

```mysql
mysql> CREATE TABLE t_39 (
  id int(11) NOT NULL AUTO_INCREMENT,
  c int(11) DEFAULT NULL,
  d int(11) DEFAULT NULL,
  PRIMARY KEY (id),
  UNIQUE KEY (c)
) ENGINE=InnoDB;
Query OK, 0 rows affected (0.01 sec)

mysql> insert into t_39 values(null,1,1);
Query OK, 1 row affected (0.00 sec)

mysql> insert into t_39 values(null, 1, 1);
ERROR 1062 (23000): Duplicate entry '1' for key 't_39.c'	-- 表中字段 c 唯一键冲突

mysql> insert into t_39 values(null, 2, 2);		-- 插入数据
Query OK, 1 row affected (0.01 sec)

mysql> select * from t_39;
+----+------+------+
| id | c    | d    |
+----+------+------+
|  1 |    1 |    1 |
|  3 |    2 |    2 |	-- 自增主键 id 成为了 3, 不是 2.
+----+------+------+
2 rows in set (0.00 sec)

```

如上图，当表中的某个字段是唯一键时，在发生插入数据错误时，会造成自增主键 `id` 不连续的情况。

### 2.2 事务回滚

事务执行回滚后，也会导致主键 `id` 不连续。如下代码示例：

```mysql
mysql> insert into t_39 values(null, 1, 1);
Query OK, 1 row affected (0.00 sec)

mysql> select * from t_39;
+----+------+------+
| id | c    | d    |
+----+------+------+
|  1 |    1 |    1 |
+----+------+------+
1 row in set (0.01 sec)

mysql> begin;
Query OK, 0 rows affected (0.00 sec)

mysql> insert into t_39 values(null, 2, 2);
Query OK, 1 row affected (0.00 sec)

mysql> select * from t_39;
+----+------+------+
| id | c    | d    |
+----+------+------+
|  1 |    1 |    1 |
|  2 |    2 |    2 |
+----+------+------+
2 rows in set (0.00 sec)

mysql> rollback;	-- 插入语句执行回滚操作
Query OK, 0 rows affected (0.00 sec)

mysql> commit;
Query OK, 0 rows affected (0.00 sec)

mysql> insert into t_39 values(null, 2, 2);
Query OK, 1 row affected (0.00 sec)

mysql> select * from t_39;
+----+------+------+
| id | c    | d    |
+----+------+------+
|  1 |    1 |    1 |
|  3 |    2 |    2 |	-- 事务回滚，导致主键不连续
+----+------+------+
2 rows in set (0.01 sec)

```

### 2.3 批量插入数据



## 3. 自增主键不回退的原因

假如有两个并行执行的事务，在申请自增值时，为了避免两个事务申请到相同的自增值 `id` ，那么必须**加锁**，然后事务顺序申请。

1.  假设事务 `A` 申请到了 `id=2`， 事务 `B` 申请到 `id=3`，那么这时候表 `t_39` 的自增值是 `4`，之后继续执行。

2.  事务 `B` 正确提交了，但事务 `A` 出现了唯一键冲突。

3.  如果允许事务 `A` 把自增 `id` 回退，也就是把表 `t_39` 的当前自增值改回 `2`，那么就会出现这样的情况：
    表里面已经有 `id=3` 的行，而当前的自增 `id` 值是 `2`。
4.  接下来，继续执行的其他事务就会申请到 `id=2`，然后再申请到 `id=3`。这时，就会出现插入语句报错 "**主键冲突**"。

上述主键冲突的问题会导致系统性能下降。所以 `InnoDB` 引擎不允许回退自增主键。因此，只保证了**自增主键是递增的，但不保证是连续的**。

## 4. 自增锁

自增锁不是事务锁，而是每次申请完后就马上释放，以便其他事务再申请，这样可以提高并发度。

参数 `innodb_autoinc_lock_mode` 控制自增锁的加锁规则。

```mysql
mysql> show variables like 'innodb_autoinc_lock_mode';
+--------------------------+-------+
| Variable_name            | Value |
+--------------------------+-------+
| innodb_autoinc_lock_mode | 2     |
+--------------------------+-------+
1 row in set (0.00 sec)

```

