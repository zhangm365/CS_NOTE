# `libpq` 通信协议

## 1. 概述

`libpq` 是 `PostgreSQL` 的 `C` 应用程序接口。`libpq` 是一组允许客户端程序向 `PostgreSQL` 服务器发送查询请求和接收处理结果的库函数。

另外，`libpq` 也是一些其他 `PostgreSQL` 程序接口的底层引擎。

使用 `libpq` 的客户端程序需要包括头文件 `libpq-fe.h`，并且链接 `libpq` 库。
