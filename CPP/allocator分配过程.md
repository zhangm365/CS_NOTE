# `allocator` 分配机制

## 1. `std::allocator`

`std::allocator` 是 `c++` 的默认内存分配器，是一个模板。它将 **内存分配** 和 **对象构造** 分离开来。 它主要完成以下两个功能：

- 分配原始的一块内存，然后构造对象；
- 析构对象，释放分配的内存。

主要包括以下四个成员函数：

```cpp
allocator<T> a;

auto p = a.allocate(n);	// 分配一段原始的，未构造的内存；
a.deallocate(p, n);	// 释放从 T* 指针 p 中地址开始指向的内存，这块内存含 n 个类型为 T 的对象

a.construct(p, args);	// p 是 T* 类型的指针，指向一块原始内存；arg 被传递给类型为 T 的构造函数，用来在p指向的内存中构造一个对象
a.destroy(p);	// 对 p 所指的对象执行析构函数

```

### 1.1 `allocate` 函数

调用 `operator new` 分配内存空间

### 1.2 `deallocate` 函数

调用 `operator delete` 释放空间。
