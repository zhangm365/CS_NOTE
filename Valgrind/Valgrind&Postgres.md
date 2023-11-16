
# `Valgrind` & `Postgres`

`Postgres` 中支持使用 `Valgrind memcheck`，具体可以查看源码文件 `src/include/pg_config_manual.h` 中的全部细节，了解如何构建 `Postgres` 使得其支持 `Valgrind memcheck` 工具。

## 1. 配置

为了避免产生 `autovacuum` 后台守护进程的 `core dumps` 问题，可以直接关闭 `autovacuum` 配置项。

1. `postgresql.conf`

当运行 `valgrind` 工具时，可以关闭 [`autovacuum`](https://www.postgresql.org/docs/current/routine-vacuuming.html) 后台守护进程。

在配置文件 `postgresql.conf`，通过如下方式配置：

```bash
autovacuum = off
```

## 2. `Valgrind` 用法

使用如下命令检查程序 `postgres` 的内存状态：

```bash
valgrind --leak-check=full --gen-suppressions=all \
    --suppressions=src/tools/valgrind.supp --time-stamp=yes \
    --error-markers=VALGRINDERROR-BEGIN,VALGRINDERROR-END \
    --log-file=$HOME/pg-valgrind/%p.log --trace-children=yes \
    postgres --log_line_prefix="%m %p " \
    --log_statement=all --shared_buffers=64MB 2>&1 | tee $HOME/pg-valgrind/postmaster.log
```

1. 例子

如下是调试进程 `/home/bigmath/code/bigmath-db-crypt/build/debug-clang15-dynamic-ninja/postgres/bin/postgres` 的具体命令：

```bash
valgrind --leak-check=yes --gen-suppressions=all \
    --suppressions=/home/bigmath/code/bigmath-db-crypt/src/postgres/src/tools/valgrind.supp --time-stamp=yes \
    --error-markers=VALGRINDERROR-BEGIN,VALGRINDERROR-END \
    --log-file=$HOME/pg-valgrind/%p.log --trace-children=yes \
    /home/bigmath/code/bigmath-db-crypt/build/debug-clang15-dynamic-ninja/postgres/bin/postgres --log_line_prefix="%m %p " \
    --log_statement=all --shared_buffers=128MB -D /home/bigmath/disk2/pg_data -c config_file=/home/bigmath/disk2/pg_data/bsql_pg.conf -c hba_file=/home/bigmath/disk2/pg_data/bsql_hba.conf 2>&1 | tee $HOME/pg-valgrind/postmaster.log
```

以下是客户端的可执行程序 `bsqlsh` 的命令，其中文件 `~/valgrind_bsqlsh.sql` 是需要执行的 sql 语句：

```bash
valgrind --leak-check=full --show-leak-kinds=all --gen-suppressions=all \
    --suppressions=/home/bigmath/code/bigmath-db-crypt/src/postgres/src/tools/valgrind.supp --time-stamp=yes \
    --error-markers=VALGRINDERROR-BEGIN,VALGRINDERROR-END \
    --log-file=$HOME/pg-valgrind/log/%p.log --trace-children=yes \
    /home/bigmath/code/bigmath-db-crypt/build/latest/postgres/bin/bsqlsh -C -f /home/bigmath/pg-valgrind/test_sql/create_cmk.sql 2>&1 | tee $HOME/pg-valgrind/postmaster.log
```
