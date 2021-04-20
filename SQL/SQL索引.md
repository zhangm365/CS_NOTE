# SQL索引

## 1. 索引用来帮助MySQL高效获取数据的数据结构，即改善检索操作的性能。

## 2. 索引的存储分类：在存储引擎层实现

1.  B-Tree索引：最常见的索引，大多数引擎都支持B树索引；
2.  HASH索引：只有Memory引擎支持，使用场景简单；
3.  R-Tree索引(空间索引)：是MyISAM的一种特殊索引类型，主要用于地理空间数据类型；
4.  Full-text(全文索引)：也是MyISAM的一种特殊索引类型，InnoDB现在也支持全文索引；

## 2. 创建索引

```mysql
create index prod_name_ind on Products (prod_name); -- 在表Products中的列prod_name上创建索引名prod_name_ind
```











