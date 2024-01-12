
# checkpoint

## 1. checkpoint 概念

因为对数据页的修改是缓存在 `buffer pool` 中，这些缓存的数据页在某个时刻会刷新写入到数据文件（落盘）。 `checkpoint` 是已成功写入数据文件的最新更改（由 `LSN` 值表示）的记录。
`checkpoint` 是一个 `LSN` 值，表示在这个 `LSN` 之前的所有更改都已经写入到数据文件中了，可用于崩溃恢复。
