# `gdb` 调试 `pgsql` 中查询语句的流程

## 1. `pgsql` 数据库服务的启动

### 1. 启动数据库

    编译源码后，会在 `/usr/local/pgsql/bin` 目录下生成数据库相关的可执行程序，例如 `initdb`，`pg_ctl`，`psql` 等，其中 `psql` 用于连接数据库:

    ```bash
    # 初始化数据库服务
    /usr/local/pgsql/bin/initdb -D /usr/local/pgsql/data

    # 启动数据库服务
    /usr/local/pgsql/bin/pg_ctl -D /usr/local/pgsql/data -l logfile start

    # 通过 psql 连接默认数据库 postgres
    /usr/local/pgsql/bin/psql postgres
    ```

### 2. 调试过程

查看 `psql` 进程的 `pid`：

    ```bash
    ps aux | grep psql
    
    # 通过 gdb 命令调试该进程：
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
            // 创建 socket，通过 socket 连接数据库
            pset.db = PQconnectdbParams(keywords, values, true);
            // 调用主循环，stdin 是一个文件指针，指向标准输入流，它的类型就是 FILE*。 
            // line: 414
            int successResult = MainLoop(stdin);
        }
        ```

2. `MainLoop` 函数

    主循环函数读取用户输入的 `SQL` 语句，然后调用 `SendQuery` 函数：

        ```c
        // src/bin/psql/mainloop.c
        /*
            * Main processing loop for reading lines of input
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
        // src/bin/psql/common.c
        // Send a query to the backend, and tell the user about any errors.
        PGresult *
        SendQuery(const char *query) {
            // ...
            // PQexec 函数是 libpq 库中的函数，用于向数据库发送查询语句
            // line: 1451
            PGresult *results = PQexec(pset.db, query);
            // ...
            // 处理查询结果
            OK = ProcessResult(&results);
        }
        ```

4. `PQexec` 函数
    向后端发送查询语句。

        ```c
        /* 
         * PQexec: src/interfaces/libpq/fe-exec.c
         * send a query to the backend and package up the result in a PGresult.
         */ 
        PGresult *
        PQexec(PGconn *conn, const char *query) {
            // ...
            // line: 1901
            if (!PQsendQuery(conn, query))
                return NULL;
            // ...
        }
        ```

5. `PQsendQuery` 函数
    提交查询语句。

        ```c
        /* PQsendQuery: src/interfaces/libpq/fe-exec.c
        * Submit a query, but don't wait for it to finish
        */
        int
        PQsendQuery(PGconn *conn, const char *query) {
            // ...
            /* construct the outgoing Query message */
            if (pqPutMsgStart('Q', false, conn) < 0 ||
                    pqPuts(query, conn) < 0 ||
                    pqPutMsgEnd(conn) < 0) {

                pqHandleSendFailure(conn);
                return 0;
            }

            // Give the data a push.
            if (pqFlush(conn) < 0) {
                pqHandleSendFailure(conn);
                return 0;
            }
        }
        ```
6. `pqFlush` 函数

    将 `output buffer` 中的数据通过 `socket` 发送给 `backend`。

        ```c
        /* pqFlush: src/interfaces/libpq/fe-misc.c
         * Flush any data waiting in the output buffer.
         */
        int
        pqFlush(PGconn *conn) {
            if (conn->Pfdebug)
                fflush(conn->Pfdebug);
            // 如果缓冲区的数据大于 0，则调用 pqSendSome 函数发送数据
            if (conn->outCount > 0)
                return pqSendSome(conn, conn->outCount);

            return 0;
        }
        ```

7. `pqSendSome` 函数
    调用 `send` 函数将数据发送到 `socket` 中。

        ```c
        /*
         * pqSendSome: src/interfaces/libpq/fe-misc.c
         */
        static int
        pqSendSome(PGconn *conn, int len) {
            // ...
            /* Write data to a secure connection.
             * 调用 send 函数将数据发送到 socket 中.
             */
            int sent = pqsecure_write(conn, ptr, len);
        }
        
        ```
