# explain 命令

- [explain 命令](#explain-命令)

`Using temporary` ：使用内存临时表；
`Using index` ：使用覆盖索引，不需要回表；
`Backward index scan` ：在索引 `id` 字段上使用 `order by id desc` 条件时，表示反向扫描；
`Using filesort` ：使用排序；

