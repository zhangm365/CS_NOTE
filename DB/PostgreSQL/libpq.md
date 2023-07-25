# `libpq` 通信协议

## 1. 概述

`libpq` 是 `PostgreSQL` 的 `C` 应用程序接口。`libpq` 是一组允许客户端程序向 `PostgreSQL` 服务器发送查询请求和接收处理结果的库函数。

另外，`libpq` 也是一些其他 `PostgreSQL` 程序接口的底层引擎。

使用 `libpq` 的客户端程序需要包括头文件 `libpq-fe.h`，并且链接 `libpq` 库。

## 2. 程序运行时缺少某些动态库

```bash
# 运行某个可执行程序时，提示缺少某个动态库，例如 libpq.so.5
$ symbol lookup error: /usr/local/lib/libpq.so.5: undefined symbol: _Z13libpq_reallocPvmm

# 查看该动态库的依赖关系
$ ldd /usr/local/lib/libpq.so.5

# 使用解码 c++ 名称修饰的实用程序 c++filt 查看编码后的符号名
$ c++filt _Z13libpq_reallocPvmm
libpq_realloc(void*, unsigned long, unsigned long)
# 查看该动态库的符号表
$ nm -A /usr/local/lib/libpq.so.5 | grep libpq_realloc
```
