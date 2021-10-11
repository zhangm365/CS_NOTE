# `redis` 的字符串结构

## 1. 简单动态字符串

`redis` 中没有直接使用 `C` 语言传统的字符串表示方法，而是定义了一种新的数据结构，为简单动态字符串（`simple dynamic string, SDS`）。

```c
struct __attribute__ ((__packed__)) sdshdr16 {
    uint16_t len;    /* 字符串已占用空间 */
    uint16_t alloc;    /* 字节数组分配的空间长度 */
    unsigned char flags;     /* SDS 类型 */
    char buf[];    /* 字节数组：实际存储字符串的位置 */
};
```

其中 `__attribute__ ((__packed__))` 表示告诉编译器，在编译对应的结构体时，不要采用字节对齐的方式，而是采用 **紧凑的方式分配内存**。

## 2. `SDS` 的优点

### 2.1 提供更加高效的 `API` 操作

### 2.2 可以安全存储二进制数据

### 2.3 兼容 `C` 字符串操作函数

