# 源码编译

## 1. ubuntu 编译安装

```bash
# https://wiki.postgresql.org/wiki/Working_with_Git

# 1. install dependencies
sudo apt install build-essential libreadline-dev zlib1g-dev flex bison libxml2-dev libxslt-dev libssl-dev libxml2-utils xsltproc ccache

## icu library
sudo apt install icu-devtools libicu-dev

# 2. 直接下载源码包 https://www.postgresql.org/ftp/source/
tar -jxvf postgresql-version.tar.bz2

# 或 git clone source code
# git clone https://git.postgresql.org/git/postgresql.git
# cd postgresql

# 编译 postgresql: https://www.postgresql.org/docs/current/install-short.html

# 具体编译配置参数可以查看：./configure --help
# 开启 debug 和 dtrace
./configure --enable-debug --enable-dtrace
make

sudo make install
# 可以不用增加新用户，直接使用当前默认用户
# adduser postgres
mkdir -p /usr/local/pgsql/data

# 修改目录的权限为当前 username 用户
chown -R username /usr/local/pgsql/data
# su - postgres

# 初始化数据目录
/usr/local/pgsql/bin/initdb -D /usr/local/pgsql/data
# 启动数据库
/usr/local/pgsql/bin/pg_ctl -D /usr/local/pgsql/data -l logfile start
# 创建数据库 test
/usr/local/pgsql/bin/createdb test
# 连接数据库 test
/usr/local/pgsql/bin/psql test


# 添加环境变量
export PGPATH=/usr/local/pgsql
export PATH=$PGPATH/bin:$PATH

# 停止数据库(https://www.postgresql.org/docs/current/app-pg-ctl.html)
pg_ctl start [-D datadir] [-l filename]

```

## 2. `PostgreSQL` 版本号

```bash
# 在根目录的 configure 文件中查看版本号
PACKAGE_VERSION
```
