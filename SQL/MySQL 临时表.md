[toc]

# MySQL 临时表

-----------------------

## 1. 临时表

在创建表时，表名前面加 `temporary` 可以指定要创建的表为临时表。但是临时表不等同于内存表，当创建临时表并指定引擎是 `memory` 时，该临时表才为内存表，否则为普通临时表。内存表的数据存在内存中，重启后表会被清空，而临时表的数据会存在磁盘上。
临时表在创建它的线程退出后，这个临时表会被自动删除。

```mysql
-- 创建一个内存临时表
create temporary table t(id int primary key)engine = memory;

-- 创建一个普通临时表
create temporary table t(id int primary key)engine = innodb; 	


-- 创建一个普通表
create table t(id int primary key);

```

### 1.1 临时表的特点

-   临时表只对创建它的`session` 可见，其他的 `session` 不能访问这个临时表。因此，不同 `session` 可以创建同名的临时表；
-   临时表可以与普通表重名；
-   当一个 `session` 中含有同名的临时表和普通表时，`show create` 命令，以及对表的增删改查操作都是对临时表的操作；
-   `show tables` 不显示临时表。

## 2. 临时表与主备复制

当 `binlog` 日志是 `row-based` 格式时，`binlog` 不会记录临时表的创建等操作。

