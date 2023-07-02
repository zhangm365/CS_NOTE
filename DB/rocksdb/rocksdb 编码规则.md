
# `RocksDB` 中 `key` 和 `value` 的编码规则

## 1. `key` 的编码规则

`RocksDB` 中的 `key` 是一个复合键，由两部分组成：

1. 0 个或多个 hash 生成的组件；
2. 0 个或多个有序组件。
