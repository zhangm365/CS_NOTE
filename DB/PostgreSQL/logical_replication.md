# `PostgreSQL logical replication`

[逻辑复制](https://www.postgresql.org/docs/current/logical-replication.html)是一种根据复制标识（通常是主键）来复制数据对象及其更改的方法。它是在 `PostgreSQL 12` 版本中引入的。

逻辑复制不同于物理复制，物理复制是使用精确的块地址和逐字节复制的，而逻辑复制是从 `WAL` 中构建逻辑**数据修改流**。
