
# `MySQL sql` 语句用法

记录 `MySQL` 常见的 `sql` 语句。

<!-- TOC -->
- [`MySQL sql` 语句用法](#mysql-sql-语句用法)
  - [1. 数据库信息](#1-数据库信息)
  - [2. `DDL` 语句](#2-ddl-语句)
  - [3. `DML` 语句](#3-dml-语句)
  - [4. 查看 binlog 日志](#4-查看-binlog-日志)
<!-- /TOC -->

## 1. 数据库信息

连接数据库。

```bash
# 使用 -p 进行密码登录 
mysql -h host -u user -p
Enter password: ***
```

```sql
-- 版本，日期
SELECT VERSION(), CURRENT_DATE;
-- 查看当前用户
SELECT USER();
-- 查询数据库
SHOW DATABASES;
-- 切换数据库
use db_name;
-- 查询表
SHOW TABLES;

-- 显示表的结构
DESCRIBE table_name;
```

## 2. `DDL` 语句

基本和其他数据库语法相同，仅记录特殊用法。

```bash

```

## 3. `DML` 语句

基本和其他数据库语法相同，仅记录特殊用法。

## 4. 查看 binlog 日志

如何查看 `MySQL` 的 `binlog` 日志。

```sql
        -- 查看 binlog 日志
        show variables where variable_name in ('log_bin', 'binlog_format', 'binlog_row_image', 'gtid_mode', 'enforce_gtid_consistency');

        show variables like 'datadir';
```
