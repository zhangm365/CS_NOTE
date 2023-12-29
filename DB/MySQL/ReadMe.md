
# 记录 `MySQL` 的学习笔记

## 1. 报错信息

安装后的数据库访问主要存在以下两个错误。

1. ERROR 1698 (28000): Access denied for user 'root'@'localhost'

    每次通过 mysql 连接数据库必须使用 `root` 权限，否则出现这个错误。

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
