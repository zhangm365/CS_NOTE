- [MySQL binlog&redolog](#mysql-binlogredolog)
  - [1. binlog 写入机制](#1-binlog-写入机制)
    - [1.1 `binlog` 写入逻辑](#11-binlog-写入逻辑)
    - [1.2 binlog cache 内存](#12-binlog-cache-内存)
    - [1.3 sync_binlog 参数](#13-sync_binlog-参数)
  - [2. redolog 写入机制](#2-redolog-写入机制)
    - [2.1 `redo log` 写入逻辑](#21-redo-log-写入逻辑)
    - [2.2  `innodb_log_buffer_size`](#22--innodb_log_buffer_size)
    - [2.3 `innodb_flush_log_at_trx_commit` 参数](#23-innodb_flush_log_at_trx_commit-参数)
    - [2.4 innodb_flush_log_at_timeout](#24-innodb_flush_log_at_timeout)

# MySQL binlog&redolog

[MySQL 23 讲](https://time.geekbang.org/column/article/76161)

## 1. binlog 写入机制

`binlog` 日志属于 `MySQL server` 层，是逻辑日志，记录的是 `SQL` 语句的原始逻辑。它采用追加写的方式，写完一定的文件大小后切换到下一个文件中。

### 1.1 `binlog` 写入逻辑

在事务执行过程中，先把日志写到 `binlog cache` 内存中；然后事务提交时，再把 `binlog cache` 写入 `binlog` 文件中。一个事务的 `binlog` 是不能被拆开的，因此，不论执行的事务多大， 都要确保 `binlog` 一次写入。

### 1.2 binlog cache 内存

系统给每个执行线程单独分配了一块内存 `binlog cache` ，参数 `binlog_cache_size` 控制这块内存的大小。事务在执行过程中，产生的日志先写入 `binlog cache` 内存中。

### 1.3 sync_binlog 参数

参数 `sync_binlog` 控制 `MySQL server` 层将 `binlog` 日志同步到磁盘的频率，有以下几个设置选项：

1. `sync_binlog = 0 ` ，禁止 `MySQL server` 层将 `binlog` 日志刷新到磁盘中；在这种情况下，`binlog` 日志文件只能依靠 `OS` 像对待普通文件一样将这个文件刷到磁盘保存，但是会丢失提交的事务；
2. `sync_binlog = 1`，`MySQL` 系统的默认设置，表示每次事务提交时，将 `binlog` 日志 `fsync` 到磁盘；这个是最安全的设置，保证了事务不会从 `binlog` 日志中丢失；但增加了磁盘 `IO` 次数，对数据库性能有一定的影响；
3. `sync_binlog = N ( N > 1 )`，在累计 `N` 个事务的 `binlog` 提交后才将这组日志一起 `fsync` 到磁盘；可以提高系统的性能，但是增加了数据丢失的可能性；在掉电或系统崩溃后，可能会丢失 `server` 层已提交的事务但还没有同步到 `binlog` 文件中。

## 2. redo log 写入机制

`MySQL` 提供了 `WAL` 机制，全称为 `Write-Ahead Logging`，即先写日志，再写磁盘，可以减少磁盘 `IO` 的次数。 `WAL` 的速度很快，提高了数据库性能。`InnoDB` 引擎中的 `redo log` 日志就是用来实现这个功能的日志文件。`redo log` 日志文件是物理日志，记录的是 "数据页上做了什么修改"。它采用循环写的方式，因为是固定的文件大小，用完后会覆盖之前的记录。

`WAL` 机制的主要优势如下：

1. `redo log` 和 `binlog` 都是顺序写，这样将磁盘的随机写转为顺序写；
2. `MySQL` 的组提交机制，可大幅降低磁盘的 `IOPS` 消耗；（ `IOPS` ：单位时间内系统能处理的 `I/O` 请求数量 ）

### 2.1 `redo log` 写入逻辑

类似地，`redo log` 也是先写入 `redo log buffer` 内存中；但是，并不需要将 `redo log` 中每次生成的内容后都直接持久化到磁盘中的。

### 2.2  `innodb_log_buffer_size`

`InnoDB` 中控制 `redo log buffer` 的大小，默认是 `16M`。`redo log buffer` 内存是全局共享的。

### 2.3 `innodb_flush_log_at_trx_commit` 参数

为了控制 `redo log` 的写入策略，`InnoDB` 提供了 `innodb_flush_log_at_trx_commit` 参数，有以下几种取值：

1. 设置为 `0`， `redo log` 只留在 `redo log buffer`内存中，数据丢失的风险最大；
2. 设置为 `1`，这是系统的默认设置。表示每次事务提交时都将 `redo log` 持久化到磁盘；
3. 设置为 `2`，每次事务提交时，`redo log` 只被写入文件系统的 `page cache` 中；

`InnoDB`有一个后台线程，每隔 `1` 秒会刷新 `redo log buffer` 中的内容，先调用 `write` 将日志写入文件系统中`page cache`中，然后调用 `fsync`刷新到磁盘中。综上，在参数 `innodb_flush_log_at_trx_commit` 设置为 `0` 或 `2`，都是由 `InnoDB` 后台线程刷新完成的，但是这不能保证 `100%` 成功。有时由于 `DDL` 操作或其他`InnoDB` 活动，这个刷新操作可能会很频繁，但有时由于调度问题会很慢。这样的情况下，刷新日志操作和 `innodb_flush_log_at_trx_commit` 设置是无关的。

### 2.4 innodb_flush_log_at_timeout

控制 `InnoDB` 引擎写入和刷新 `redo log` 的频率，单位是秒，默认值是 `1` 秒，即每秒对 `redo log` 进行刷新到磁盘中。

