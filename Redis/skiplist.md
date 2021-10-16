# `skiplist`

跳跃表是一种有序数据结构，它通过在每个节点中维持多个指向其他节点的指针，从而达到快速访问节点的目的。

跳表在有序集合的底层实现之一。

## 1. 跳表节点

如下是跳表节点的数据结构：

```c
typedef struct zskiplistNode {
    sds ele;    // sds 对象
    double score;    // 分值：按分值从小到大排序
    struct zskiplistNode *backward;    // 后退指针
    struct zskiplistLevel {    // 层数数组
        struct zskiplistNode *forward;    // 前进指针
        unsigned long span;    // 跨度：记录两个节点间的距离
    } level[];
}zskiplistNode; 
```

如下，是 `3` 层 `level` 数组的节点结构：

<img src="./pics/skiplist.png" style="zoom:30%;" />

## 2. 跳表

```c
typedef struct zskiplist {
    struct zskiplistNode *header, *tail;	// 跳表的头尾指针
    unsigned long length;	// 跳表中的节点个数
    int level;    // 保存跳表中的节点的最大层数
} zskiplist;
```

