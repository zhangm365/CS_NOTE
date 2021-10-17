- [`redis` 对象](#redis-对象)
- [1. 对象的类型和编码](#1-对象的类型和编码)
  - [1.1 类型](#11-类型)
  - [1.2 编码和底层实现](#12-编码和底层实现)

# `redis` 对象

`redis` 数据库构造了一个对象系统，这个系统包括字符串对象、列表对象、哈希对象、集合对象和有序集合对象这五种类型。

# 1. 对象的类型和编码

`redis` 中使用对象表示数据库中的键和值，每次创建一个键值对时，至少会创建两个对象，一个对象用于键值对的键（键对象），一个对象用于键值对的值（值对象）。`redis` 中的每个对象都由一个 `redisObject` 结构体表示，`type` 是类型属性、`encoding` 是编码属性、`ptr` 是指向底层实现数据结构的指针。

```c
// server.h
typedef struct redisObject {
    unsigned type:4;	// 类型属性：5种
    unsigned encoding:4;    // 编码属性
    unsigned lru:LRU_BITS; /* LRU time (relative to global lru_clock) or
                            * LFU data (least significant 8 bits frequency
                            * and most significant 16 bits access time). */
    int refcount;    // 引用计数
    void *ptr;    // 指向实现数据结构的指针
} robj;
```

## 1.1 类型

|     类型     | 对象名称 | `type`命令输出 |
| :----------: | :------: | :------------: |
| `OBJ_STRING` |  字符串  |    `string`    |
|  `OBJ_LIST`  |   列表   |     `list`     |
|  `OBJ_HASH`  | 哈希对象 |     `hash`     |
|  `OBJ_SET`   |   集合   |     `set`      |
|  `OBJ_ZSET`  | 有序集合 |     `zset`     |

以下是不同对象类型的示例，可以通过命令 `type` 来查看键对应的值对象类型：

```shell
127.0.0.1:6379> SET msg "hello world"
OK
127.0.0.1:6379> type msg
string

127.0.0.1:6379> HMSET profile name "Tom" age 25 career "Programmer"
OK
127.0.0.1:6379> type profile
hash

127.0.0.1:6379> rpush numbers 1 3 5
(integer) 6
127.0.0.1:6379> type numbers
list

127.0.0.1:6379> SADD fruits apple banana cherry
(integer) 3
127.0.0.1:6379> type fruits
set

127.0.0.1:6379> ZADD price 8.5 apple 5.0 banana 6.0 cherry
(integer) 3
127.0.0.1:6379> type price
zset

```

## 1.2 编码和底层实现

对象的`ptr`指针指向对象的底层实现数据结构，而这些数据结构由对象的`encoding`属性决定。`encoding`记录了对象所使用的编码，如下表格：

|     类型     |           编码           |                   对象                   |
| :----------: | :----------------------: | :--------------------------------------: |
| `OBJ_STRING` |    `OBJ_ENCODING_INT`    |   使用整数值（`long`）实现的字符串对象   |
| `OBJ_STRING` |  `OBJ_ENCODING_EMBSTR`   | 使用`embstr`编码的 `sds`实现的字符串对象 |
| `OBJ_STRING` |    `OBJ_ENCODING_RAW`    |       使用 `sds` 实现的字符串对象        |
|  `OBJ_LIST`  |  `OBJ_ENCODING_ZIPLIST`  |        使用压缩列表实现的列表对象        |
|  `OBJ_LIST`  | `OBJ_ENCODING_QUICKLIST` |          使用快表实现的列表对象          |
|  `OBJ_HASH`  |  `OBJ_ENCODING_ZIPLIST`  |        使用压缩列表实现的哈希对象        |
|  `OBJ_HASH`  |    `OBJ_ENCODING_HT`     |          使用字典实现的哈希对象          |
|  `OBJ_SET`   |  `OBJ_ENCODING_INTSET`   |        使用整数集合实现的集合对象        |
|  `OBJ_SET`   |    `OBJ_ENCODING_HT`     |          使用字典实现的集合对象          |
|  `OBJ_ZSET`  |  `OBJ_ENCODING_ZIPLIST`  |        使用压缩列表实现的有序集合        |
|  `OBJ_ZSET`  | `OBJ_ENCODING_SKIPLIST`  |          使用跳表实现的有序集合          |

命令`object encoding`可以查看值对象的编码类型：

```shell
127.0.0.1:6379> object encoding msg
"embstr"

```

