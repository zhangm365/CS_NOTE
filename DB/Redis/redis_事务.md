- [`redis`事务](#redis事务)
- [1. 事务](#1-事务)
  - [1.1 事务的实现](#11-事务的实现)
    - [1.1.1 事务开始](#111-事务开始)
    - [1.1.2 命令入队](#112-命令入队)
    - [1.1.3 事务执行](#113-事务执行)


# `redis`事务

# 1. 事务

事务提供了一种将多个命令请求打包，然后一次性、顺序性地执行多个命令的机制。事务执行要么全部成功，要么全部失败。

`Redis`通过`MULTI、EXEC、WATCH`等命令来实现事务的功能。

## 1.1 事务的实现

一个完整的事务分为三个阶段：事务开始、命令入队、事务执行。

### 1.1.1 事务开始

命令`MULTI`的执行标志着事务的开始。

### 1.1.2 命令入队

当一个客户端处于事务状态时，服务器会根据客户端发送的不同命令来执行不同的操作：

1. 当客户端发送的是`EXEC、DISCARD、WATCH、MULTI`四个命令的其中一个，那么服务器立即执行这个命令；
2. 否则服务器会将客户端发送的命令放入一个事务队列中，然后向客户端发送`QUEUED`回复。

事务队列的数据结构如下：

每个`Redis`客户端都有自己的事务状态，这个状态保存在`client`结构体的`mstate`：

```c
typedef struct client {
    ...
    // 事务状态
    multiState mstate;      /* MULTI/EXEC state */
    ...
} client;
```

`multiState`结构如下：

```c
typedef struct multiState {
    // 事务队列，FIFO
    multiCmd *commands;     /* Array of MULTI commands */
    // 已入队命令个数
    int count;              /* Total number of MULTI commands */
    ...
} multiState;
```

事务队列是一个`multiCmd`类型的数组，包括命令参数、命令个数、命令实现的函数指针：

```c
/* Client MULTI/EXEC state */
typedef struct multiCmd {
    // 命令参数
    robj **argv;
    // 命令个数
    int argc;
    // 命令指针
    struct redisCommand *cmd;
} multiCmd;
```

### 1.1.3 事务执行

当处于事务状态的客户端向服务器发送`EXEC`命令时，这个命令将立即被执行。服务器会遍历这个客户端的事务队列，执行事务队列中保存的所有命令，然后返回执行结果给客户端。

```shell
127.0.0.1:6379> multi
OK
127.0.0.1:6379(TX)> set name "hello world"
QUEUED
127.0.0.1:6379(TX)> set author "redis"
QUEUED
127.0.0.1:6379(TX)> get name
QUEUED
127.0.0.1:6379(TX)> exec
1) OK
2) OK
3) "hello world"
127.0.0.1:6379>
```

