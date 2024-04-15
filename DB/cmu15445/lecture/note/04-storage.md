
# storage 笔记

## 1. tuple-oriented storage

基于 heap 结构组织的磁盘文件和数据页中使用 slot array 组织 tuple 的方式，记录如何插入和更新一个 tuple。

1. 如何插入一个新 tuple？

    插入一个新 tuple 的步骤如下：

    - 检查堆文件组织的页目录，检索含有空闲 slot 的数据页；

    - 从磁盘读取该页到内存；

    - 检查该页中的 slot array 空闲位置，插入新 tuple。

2. 如何更新一个存在的 tuple？

    使用 record id 更新一个存在的 tuple。

    - 根据页目录找到对应的数据页；

    - 从磁盘读取该页到内存；

    - 使用 slot array 找到对应的 tuple；

    - 如果新数据和原 tuple 空间大小相同，直接覆盖；否则，将原 tuple 标记为删除，在合适的空闲位置插入新 tuple。
