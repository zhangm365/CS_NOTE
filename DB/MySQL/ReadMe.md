
# 记录 `MySQL` 的学习笔记

## 1. 安装

[官网](https://dev.mysql.com/downloads/mysql/) 下载对应的安装包。

```bash
# 1. 启动 mysqld 服务
sudo systemctl start mysqld
sudo systemctl status mysqld

# 2. 连接，需要输入密码
sudo mysql -u root -p
## 2.1 查询 root 临时密码
sudo grep 'temporary password' /var/log/mysqld.log
2024-05-11T02:14:55.998313Z 6 [Note] [MY-010454] [Server] A temporary password is generated for root@localhost: QpZL<rjVv5ow
```

登录数据库后，修改用户密码：

```sql
--- 2.2 修改密码，满足严格的密码策略
ALTER USER 'root'@'localhost' IDENTIFIED BY 'MyNewPass2024!';

--- 2.3 查看密码策略
SHOW VARIABLES LIKE 'validate_password%';

--- 2.4 修改密码策略为 low level
set global validate_password.length=6;
SET GLOBAL validate_password.policy = 0;
FLUSH PRIVILEGES;

--- 2.5 重新设置为简单密码
ALTER USER 'root'@'localhost' IDENTIFIED BY 'xxx';
FLUSH PRIVILEGES;

--- 3. root 用户远程访问
use mysql;
select user, host from user;
update user set host="%" where user="root";
FLUSH PRIVILEGES;

# 3. create new user
CREATE USER 'user_name'@'%' IDENTIFIED BY 'passwd';
GRANT ALL PRIVILEGES ON *.* TO 'user_name'@'%';

```

### 1.1 ubuntu 操作

ubuntu 的数据库访问主要存在以下两个错误。

1. ERROR 1698 (28000): Access denied for user 'root'@'localhost'

    每次通过 `mysql` 连接数据库必须使用 `root` 权限，否则出现这个错误。

    ```bash
    sudo mysql -u root # I had to use "sudo" since it was a new installation

    mysql> USE mysql;
    mysql> SELECT User, Host, plugin FROM mysql.user;

    +------------------+-----------------------+
    | User             | plugin                |
    +------------------+-----------------------+
    | root             | auth_socket           |
    | mysql.sys        | caching_sha2_password |
    | debian-sys-maint | caching_sha2_password |
    +------------------+-----------------------+

    # ubuntu 使用 auth_socket 插件进行认证。

    sudo mysql -u root # I had to use "sudo" since it was a new installation

    mysql> USE mysql;
    mysql> UPDATE user SET plugin='mysql_native_password' WHERE User='root';
    mysql> FLUSH PRIVILEGES;
    mysql> exit;

    sudo systemctl restart mysql

    ```

2. ERROR 2003 (HY000): Can't connect to MySQL server on 'host_ip' (111)

    `mysql -u root -h host_ip -p` 指定主机ip地址访问数据库，显示这个错误。

    ```bash
    # 1.
    sudo vim /etc/mysql/my.cnf

    # 2. comment bind-address = 127.0.0.1 using the # symbol

    # restart your MySQL server once.
    sudo systemctl restart mysql

    # In Step 1, if you cannot find bind-address in the my.cnf file, look for it in file.
    sudo vim /etc/mysql/mysql.conf.d/mysqld.cnf
    ```
