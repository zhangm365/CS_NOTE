# `gdb` 调试 `pgsql` 中查询语句的流程

## 1. `pgsql` 数据库服务的启动

### 1. 启动数据库

    编译源码后，会在 `/usr/local/pgsql/bin` 目录下生成数据库相关的可执行程序，例如 `initdb`，`pg_ctl`，`psql` 等，其中 `psql` 用于连接数据库:

    ```bash
    # 初始化数据库服务
    /usr/local/pgsql/bin/initdb -D /usr/local/pgsql/data

    # 启动数据库服务
    /usr/local/pgsql/bin/pg_ctl -D /usr/local/pgsql/data -l logfile start

    # 通过 psql 可执行程序连接默认数据库 postgres
    /usr/local/pgsql/bin/psql postgres
    ```

### 2. 调试过程

    通过命令 `psql` 连接数据库后，查看该进程的 `pid`：

    ```bash
    ps aux | grep psql
    ```

    然后通过 `gdb` 命令调试该进程：

    ```bash
    gdb
    attach <pid>

    bt
    ```

### 3. 函数调用过程

从 `gdb` 调试的堆栈信息可以看出 `psql` 程序的流程如下：

1. `main` 函数

    首先从 `main` 函数入口开始，主要是解析命令行参数，然后调用 `MainLoop` 函数：

        ```c
        // src/bin/psql/main.c
        int
        main(int argc, char *argv[]) {
            // ...
            // 连接数据库
            pset.db = PQconnectdbParams(keywords, values, true);
            // 调用主循环，stdin 是一个文件指针，指向标准输入流，它的类型就是 FILE*。 
            // line: 414
            int successResult = MainLoop(stdin);
        }
        ```

2. `MainLoop` 函数

        ```c
        // src/bin/psql/mainloop.c
        /* Main processing loop for reading lines of input
         * and sending them to the backend.
         */

        // 
        int
        MainLoop(FILE *source) {

            // execute query  
            if (conditional_active(cond_stack)) {
                // line: 429
                success = SendQuery(query_buf->data); // 发送查询语句
            }
        }
        ```

3. `SendQuery` 函数

    `SendQuery` 函数是 `psql` 程序中发送查询语句的函数，它会调用 `PQexec` 函数：

        ```c
        // src/bin/psql/command.c
        // Send a query to the backend, and tell the user about any errors.
        PGresult *
        SendQuery(const char *query) {
            // ...
            // PQexec 函数是 libpq 库中的函数，用于向数据库发送查询语句
            // line: 1451
            PGresult *results = PQexec(pset.db, query);
            // ...
        }
        ```
4. `PQexec` 函数
