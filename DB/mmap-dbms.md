# 为什么不要在 `DBMS` 中使用 `mmap`？

基于论文 "Are You Sure You Want to Use MMAP in Your Database Management System?" 的总结。

`DBMS` 中使用 `mmap` 实现内存映射文件 `I/O` 来替代传统的 `buffer pool` 机制。优点在于减少内核和用户空间之间的文件 `I/O` 的次数，提高 `I/O` 性能。

例如，[`SQLite`](https://www.sqlite.org/mmap.html) 和 `MongoDB` 都使用基于 `mmap` 的存储引擎，但从 2019 年开始 `MongoDB` 已经完全不再使用 `mmap`，而是使用 [`WiredTiger`](https://www.mongodb.com/docs/manual/core/storage-engines/) 引擎。

`MongoDB` 早期使用基于 `mmap` 的存储引擎的设计有许多缺陷，例如为了数据正确性使用复杂地复制方案和不能在辅助存储设备上压缩数据。

但是，`mmap` 也有一些缺点：

1. 事务安全；





