[toc]

# 慢查询日志

----------------------

## 1. 慢查询日志命令

### 1.1 `slow_query_log` ：控制慢查询日志是否开启状态

默认是关闭的，可以通过以下命令查看：

```mysql
mysql> show variables like 'slow_query_log';
+----------------+-------+
| Variable_name  | Value |
+----------------+-------+
| slow_query_log | OFF   |
+----------------+-------+
1 row in set (0.00 sec)

```

设置慢查询日志为开启状态：
`set global slow_query_log = ON;`

### 1.2 `slow_query_log_file` ：慢查询日志存储位置

```mysql
mysql> show variables like 'slow_query_log_file';
+---------------------+--------------------------------+
| Variable_name       | Value                          |
+---------------------+--------------------------------+
| slow_query_log_file | /var/lib/mysql/ubuntu-slow.log |
+---------------------+--------------------------------+
1 row in set (0.00 sec)
```

### 1.3 `long_query_time` ：慢查询记录时间（秒）

这个值表示的是语句执行超过这个阈值就会被记录到慢查询日志中，默认是 `10s`。可以将该值修改为任意值。如下表示修改为 `0` 秒，这时所有的执行语句都被记录在慢查询日志中。**设置该值后，需要重启连接后才生效。**

```mysql
mysql> set global long_query_time = 0;
Query OK, 0 rows affected (0.00 sec)
```

### 1.4 查看慢查询日志内容

`sudo cat /var/lib/mysql/ubuntu-slow.log `

