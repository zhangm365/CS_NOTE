
# PostgreSQL 常见用法

# 1. 基本命令

```sql
-- 查看数据库中的当前连接信息
select * from pg_stat_activity

-- 获取当前连接的进程 pid
select pg_backend_pid()
```
