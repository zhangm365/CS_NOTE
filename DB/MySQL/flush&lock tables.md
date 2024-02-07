
# `FLUSH | LOCK TABLES` Statements

- [`FLUSH | LOCK TABLES` Statements](#flush--lock-tables-statements)
  - [1. 语法](#1-语法)
  - [2. `FLUSH TABLES` Syntax](#2-flush-tables-syntax)
  - [3. `LOCK TABLES` Statement](#3-lock-tables-statement)
  - [4. `FLUSH TABLES WITH READ LOCK` vs `LOCK TABLES ... READ`](#4-flush-tables-with-read-lock-vs-lock-tables--read)
  - [4. `FLUSH TABLES tbl_name [, tbl_name] ... WITH READ LOCK` vs `LOCK TABLES ... READ`](#4-flush-tables-tbl_name--tbl_name--with-read-lock-vs-lock-tables--read)

`[FLUSH Statement](https://dev.mysql.com/doc/refman/8.3/en/flush.html)` 用于清除或重载内部缓存、刷新表或获取锁。

默认地，`MySQL server` 会将 `FLUSH` 语句写入 `binary log` 使能它们可以复制到副本中，但可以通过 `NO_WRITE_TO_BINLOG | LOCAL` 选项来禁止写入 `binary log`。

## 1. 语法

语法格式如下：

```sql
FLUSH [NO_WRITE_TO_BINLOG | LOCAL] {
    flush_option [, flush_option] ...
  | tables_option
}

flush_option: {
    BINARY LOGS
  | ENGINE LOGS
  | ERROR LOGS
  | GENERAL LOGS
  | HOSTS
  | LOGS
  | PRIVILEGES
  | OPTIMIZER_COSTS
  | RELAY LOGS [FOR CHANNEL channel]
  | SLOW LOGS
  | STATUS
  | USER_RESOURCES
}

tables_option: {
    TABLES
  | TABLES tbl_name [, tbl_name] ...
  | TABLES WITH READ LOCK
  | TABLES tbl_name [, tbl_name] ... WITH READ LOCK
  | TABLES tbl_name [, tbl_name] ... FOR EXPORT
}
```

## 2. `FLUSH TABLES` Syntax

操作需要 `FLUSH TABLES` 或 `RELOAD` 权限。

1. `FLUSH TABLES` 关闭所有打开的表，强制关闭正在使用的表，并刷新缓存。

2. `FLUSH TABLES tbl_name [, tbl_name] ...` 关闭指定的表，强制关闭正在使用的表，并刷新缓存。

3. `FLUSH TABLES WITH READ LOCK` 关闭所有打开的表，并使用一个**全局读锁**锁定所有数据库的所有数据表，防止其他客户端对表进行写操作。该操作便于备份数据库，使用 `UNLOCK TABLES` 释放锁。

4. `FLUSH TABLES tbl_name [, tbl_name] ... WITH READ LOCK` 刷新并获取指定表的读锁。它请求获取表锁，因此需要 `LOCK TABLES` 权限。

该操作的步骤如下：

- 首先获取表的独占元数据锁。然后刷新表缓存，重新打开表并获取表锁（`LOCK TABLES ... READ`），并将元数据锁从独占降为共享锁；

>> [Metadata Lock](https://dev.mysql.com/doc/refman/8.3/en/metadata-locking.html) 用于管理数据库对象的并发访问和确保数据的一致性。元数据锁不仅适用于 tables, 还包括 schemas, procedures, functions, triggers 等。

- 在获取表锁和降级元数据锁后，其他会话仅可读不可写表。

通过 `UNLOCK TABLES` 释放锁或 `START TARNSACTION` 释放锁并开始新事务。

## 3. `LOCK TABLES` Statement

`LOCK TABLES` 用于当前会话显式获取表锁，以便与其他会话进行合作或防止其他会话在独占表期间修改表。`UNLOCK TABLES` 用于释放锁。

`LOCK TABLES` 语法如下：

```sql
LOCK TABLES
    tbl_name [[AS] alias] lock_type
    [, tbl_name [[AS] alias] lock_type] ...

lock_type: {
    READ [LOCAL]
  | [LOW_PRIORITY] WRITE
}

UNLOCK TABLES
```

`LOCK TABLES` 语句的 `READ` 锁特点如下：

- 会话使用 `READ` 锁定表，仅可读数据，不能写表；

- 多个会话可以同时请求相同表的 `READ` 锁；

- 其他会话可以读表，无需显式请求 `READ` 锁；

## 4. `FLUSH TABLES WITH READ LOCK` vs `LOCK TABLES ... READ`

`FLUSH TABLES WITH READ LOCK` 获取全局读锁。因此，`FLUSH TABLES WITH READ LOCK` 与 `LOCK TABLES ... READ` 的区别在于表锁和隐式提交两个方面：

- 在 `LOCK TABLES ... READ` 锁定当前任何表的情况下，`UNLOCK TABLES` 会隐式提交任何活跃事务，而不会提交在 `FLUSH TABLES WITH READ LOCK` 中开启的事务；

- `START TRANSACTION` 会释放 `LOCK TABLES ... READ` 获取的表锁，类似执行了 `UNLOCK TABLES` 语句，从而可以在开启的事务中执行写操作。

## 4. `FLUSH TABLES tbl_name [, tbl_name] ... WITH READ LOCK` vs `LOCK TABLES ... READ`

它们均会获取表锁，区别如下：

- 当前会话通过 `FLUSH TABLES tbl_name [, tbl_name] ... WITH READ LOCK` 在指定表上获取表锁后，其他会话无法同时对相同表获取表锁，而 `LOCK TABLES ... READ` 可以；

- `FLUSH TABLES tbl_name [, tbl_name] ... WITH READ LOCK` 可以批量获取表锁，语法简单，而 `LOCK TABLES ... READ` 需要逐个获取表锁。
