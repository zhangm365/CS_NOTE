# 源码编译

## 1. ubuntu 编译安装

```bash
# https://wiki.postgresql.org/wiki/Working_with_Git

# install dependencies
sudo apt-get install build-essential libreadline-dev zlib1g-dev flex bison libxml2-dev libxslt-dev libssl-dev libxml2-utils xsltproc ccache

# git clone source code
git clone https://git.postgresql.org/git/postgresql.git
cd postgresql

# 编译 postgresql: https://www.postgresql.org/docs/current/install-short.html

# 具体编译配置参数可以查看：./configure --help
# 开启 debug 和 dtrace
./configure --enable-debug --enable-dtrace
make
su
make install
adduser postgres
mkdir -p /usr/local/pgsql/data
chown postgres /usr/local/pgsql/data
su - postgres
/usr/local/pgsql/bin/initdb -D /usr/local/pgsql/data
/usr/local/pgsql/bin/pg_ctl -D /usr/local/pgsql/data -l logfile start
/usr/local/pgsql/bin/createdb test
/usr/local/pgsql/bin/psql test
```

## 2. `PostgreSQL` 版本号

```bash
# 在根目录的 configure 文件中查看版本号
PACKAGE_VERSION
```
