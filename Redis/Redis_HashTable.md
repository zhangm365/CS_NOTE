# 哈希表的设计与实现

# 1. 哈希表的结构

`Redis` 中哈希表的相关设计在文件 `dict.h` 和 `dict.c` 中。

## 1.1 哈希表中的每个节点定义

哈希表中的每个节点由结构体 `dictEntry`定义，如下： 

```c
typedef struct dictEntry {
    void *key;	// 指向 key 值
    union {
        void *val;	// 指向 val 值的指针
        uint64_t u64;
        int64_t s64;
        double d;
    } v;
    struct dictEntry *next;		// 指针域，指向下一个节点
    
} dictEntry;
```

含有的指针 `next` 指向下一个哈希项，用来实现 **链式哈希** 的。

## 1.2 哈希表的结构定义

```c
typedef struct dictht {
    dictEntry **table;	// 二维数组：哈希表结构
    unsigned long size;	// 哈希表的大小
    unsigned long sizemask;
    unsigned long used;	// 表中实际含有的元素大小
} dictht;
```



# 2. 哈希冲突的解法方法

当不同的键值出现在同一个桶时，那么就出现了哈希冲突。因此，采用链表法将映射到哈希表同一个桶中的节点用一个链表连接起来。

# 3. 如何实现 `rehash` ？

当哈希表中的某个桶中链表太长时，就会严重影响哈希表的查找性能。因此，`rehash` 就会扩大 `Hash` 表的空间，保证哈希表较高的查询性能。

## 3.1 `Redis` 实现 `rehash` 的思路

`Redis` 准备了两个哈希表，用于 `rehash` 时交替保存数据，其中表 `ht[0]` 用来正常的服务请求，`ht[1]` 为 `rehash` 的迁移表。

```c
typedef struct dict {
    dictType *type;
    void *privdata;
    dictht ht[2];	// 两个哈希表，用于 rehash 
    long rehashidx; // -1 表示没有进行 rehash, 否则就是在 rehash
    unsigned long iterators; /* number of iterators currently running */
} dict;
```

因此，`rehash` 过程如下：

1. 正常服务请求阶段，所有的键值对写入哈希表 `ht[0]`；
2. 当需要进行 `rehash` 时，键值对被迁移到表 `ht[1]`；
3. 最后，当迁移完成后，`ht[0]` 的空间会被释放，同时把 `ht[1]` 的地址值赋值给 `ht[0]`，`ht[1]` 表的大小重置为 `0`。

哈希表的扩容大小为原来表已用空间的 `2` 倍大小。

## 3.2 `rehash` 触发时机

`rehash` 是否触发由函数 `_dictExpandIfNeeded` 判断，出现以下条件时就触发了 `rehash` 操作：

1. `ht[0]`哈希表的初始大小是 `0`，默认初始为 `4` 个长度；
2. `ht[0]`承载的元素个数 `used` 大于表的大小 `size` 后，且允许扩大哈希表的大小（没有`RDB`子进程和`AOF` 子进程）；
3. 比值 `ht[0].used / ht[0].size > dict_force_resize_ratio` 倍后，`dict_force_resize_ratio` 默认值是 `5` 。比值 `ht[0].used / ht[0].size` 即为 **负载因子**。

## 3.3 渐进式 `rehash` 如何实现？

当原来的 `Hash` 表要进行 `rehash` 时，由于哈希表的空间扩大，原本映射到某一位置的键可能会被映射到新的位置，那么就会存在很多键的拷贝操作。键拷贝时， `Redis` 主线程无法执行其他请求，阻塞主线程，因此就会产生一定的 `rehash` 开销。

为了降低 `rehash` 的开销，`Redis` 就提出了渐进式 `rehash` 的方法。渐进式 `rehash` 的思路是 `Redis` 并不会一次性将当前 `Hash` 表中的所有键拷贝到新表中，而是分批次、渐进式进行，这样保证数据的拷贝操作对主线程的影响较小。

 代码实现在函数 `dictRehash` 中。

因为在进行渐进式`rehash`的过程中，字典会同时使用`ht[0]`和`ht[1]`两个哈希表，所以在渐进式`rehash`进行期间，字典的删除（`delete`）、查找（`find`）、更新（`update`）等操作会在两个哈希表上进行。例如，要在字典里面查找一个键的话，程序会先在`ht[0]`里面进行查找，如果没找到的话，就会继续到`ht[1]`里面进行查找，诸如此类。
另外，在渐进式`rehash`执行期间，新添加到字典的键值对一律会被保存到`ht[1]`里面，而`ht[0]`则不再进行任何添加操作，这一措施保证了`ht[0]`包含的键值对数量会只减不增，并随着`rehash`操作的执行而最终变成空表。