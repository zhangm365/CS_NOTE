
# `PostgreSQL` 基本命令
<!-- TOC -->
- [`PostgreSQL` 基本命令](#postgresql-基本命令)
  - [1. 数据库连接信息](#1-数据库连接信息)
  - [2. 数据库大小](#2-数据库大小)
  - [3. 数据表大小](#3-数据表大小)
  - [4. 数据库状态](#4-数据库状态)
  - [5. 查看索引](#5-查看索引)
  - [6. 查看建表语句](#6-查看建表语句)
<!-- /TOC -->
## 1. 数据库连接信息

```sql
-- 查看数据库中的当前连接信息
select * from pg_stat_activity;

-- 数据库连接信息
SELECT pid, usename, client_addr 
FROM pg_stat_activity 
WHERE datname ='db_name';

-- 获取当前客户端连接的服务端进程 pid
select pg_backend_pid();

-- 查看当前数据库的连接数
select count(*) from pg_stat_activity;
```

## 2. 数据库大小

```sql
-- 查看数据库大小：例如 bigmath 数据库大小 select pg_database_size('bigmath');
select pg_size_pretty(pg_database_size('db_name'));

-- 查看所有数据库的大小
select pg_database.datname, pg_size_pretty(pg_database_size(pg_database.datname)) as size from pg_database;

```

## 3. 数据表大小

```sql
-- 查看当前数据库中的所有表
\dt

-- 查看某个表的 oid
select 'table_name'::regclass::oid;

select * from pg_tables where schemaname = 'public';
--
select pg_size_pretty(pg_table_size('table_name'));

-- 查看指定 schema 里所有数据表的大小
select relname, pg_size_pretty(pg_table_size(relid)) from pg_stat_user_tables where schemaname = 'public' order by pg_table_size(relid) desc;

-- pg_relation_size 与 pg_table_size 的区别
select 
pg_relation_size(20306, 'main') as main,
pg_relation_size(20306, 'fsm') as fsm,
pg_relation_size(20306, 'vm') as vm,
pg_relation_size(20306, 'init') as init,
pg_table_size(20306), 
pg_indexes_size(20306) as indexes,
pg_total_relation_size(20306) as total;
  main  |  fsm  |  vm  | init | pg_table_size | indexes |  total 
--------+-------+------+------+---------------+---------+--------
 253952 | 24576 | 8192 |    0 |        286720 |  196608 | 483328
(1 row)

```

## 4. 数据库状态

```sql

```

## 5. 查看索引

查看某个表上的所有索引。

  ```sql
  SELECT
      indexname,
      indexdef
  FROM
      pg_indexes
  WHERE
      tablename = 'table_name';
  ```

## 6. 查看建表语句
  
  ```sql
  -- 使用 pg_dump 查看建表语句，-s 表示只导出 schema，-t 表示只导出指定表，-f 表示导出到指定文件，-W 表示提示输入密码, -U 表示指定用户名, -d 表示指定数据库
  pg_dump -U username -d databasename -W -s -t table_name -f filename.sql
  ```
