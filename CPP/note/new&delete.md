[toc]

# 一. new和delete

-------------

## 1. new 和 delete 执行步骤

1.1 `new`：先分配内存，再调用 `ctor`

```c++
string *ps = new string("hello");

// 编译器转化为以下三步：
string *ps;

void *mem = operator new(sizeof(string));	// 分配原始内存
ps = static_cast<string *>(mem)	// 转型
ps->string::string("hello");	// 调用对象的构造函数
```

1.2 `delete`：先调用 `dtor`，再释放内存

```c++
string *ps = new string("hello");
···
delete ps;

// 编译器转为以下两步
string::~string(ps);	// 析构函数
operator delete(ps);	// 释放内存
```



## 2. 自由存储区 (free store)  VS 堆 (heap)

堆是C语言和OS中的概念，是OS所维护的一种特殊内存区域，提供了动态分配的功能。在调用malloc()时就会从堆中分配，之后用free释放对应的内存空间。

自由存储区是C++中通过 **`new/delete`** 动态内存分配和释放对象的抽象概念，通过new申请的内存空间可以成为自由存储区。

几乎所有的C++编译器默认使用堆来实现自由存储。但是自由存储区和堆并不是等同的。

## 3. new和malloc的区别

|             特征             |                   `new/delete`                    |     `malloc/free`      |
| :--------------------------: | :-----------------------------------------------: | :--------------------: |
|         分配内存区域         |                    自由存储区                     |           堆           |
| 返回类型安全性(内存分配成功) |                   完整类型指针                    |        `void*`         |
|     内存分配失败的返回值     |       抛出 `bad_alloc`异常(`try_catch`捕捉)       |         `NULL`         |
|         指定内存大小         |              自动计算分配类型的大小               | 显式指出分配内存的大小 |
|      构造函数/析构函数       |            调用分配对象的构造/析构函数            |           无           |
|       两者之间相互调用       | `operate new/operate delete`可以调用`malloc/free` |  不可调用`new/delete`  |
|        是否可以被重载        |      `operate new/operate delete` 可以被重载      |          不可          |

## 4. placement new

### 		1).  `placement new`  是重载 `operator new` 的一个标准、全局的版本，不可以被自定义的版本替代。

它的原型如下：

`void* new(size_t size, void* p) throw() { return p; }`

如果在已经分配的内存上创建一个对象，使用 `new` 是不可行的。这时使用 `placement new` 即可满足需求。参数中的 `p` 实际上是指向已经存在的内存区域，`placement new` 直接返回这个指向已经分配的内存区域的指针。

### 		2). 实现方法

```c++
class MyClass{...};

// 1内存缓冲区提前分配
char *buf = new char[N*sizeof(MyClass) + size(int)];
// 2创建一个对象：调用placement new, 此步只调用了对象的构造函数
MyClass *p = new(buf) MyClass;
// 3对象销毁:一旦这个对象使用完毕, 必须人为显式调用对应的析构函数进行销毁
p->~MyClass();

```

