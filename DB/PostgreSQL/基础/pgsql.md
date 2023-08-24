
<!-- TOC -->

# `PostgreSQL` 常见用法

## 1. 数据库状态信息

```sql
-- 查看数据库中的当前连接信息
select * from pg_stat_activity;

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
select * from pg_tables where schemaname = 'public';
--
select pg_size_pretty(pg_relation_size('table_name'));

-- 查看指定 schema 里所有数据表的大小
select relname, pg_size_pretty(pg_relation_size(relid)) from pg_stat_user_tables where schemaname = 'public' order by pg_relation_size(relid) desc;
```
