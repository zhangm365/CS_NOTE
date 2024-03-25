
# 如何安装 `postgis` 扩展

在 PostgreSQL 中，`postgis` 是一个非常有用的扩展，它可以让我们在数据库中存储地理空间数据，并且提供了很多地理空间数据处理的函数。本文将介绍如何在 PostgreSQL 中安装 `postgis` 扩展。

## 1. 安装 `postgis` 扩展

```bash

## 1. 安装依赖库
# 安装依赖库使得运行 ./configure 时不会报错.
# 
sudo apt-get install libpq-dev

sudo apt install libxml2-dev

# proj lib 
sudo apt install libproj-dev

# protobuf
sudo apt install protobuf-c-compiler libjsoncpp-dev libprotobuf-dev libprotobuf-c-dev libxml2-dev

# gdal-config
sudo apt install libgdal-dev

# how to fix "postgres.h" not found. i.e, XX is the postgresql version. i.e: 15, 16
sudo apt install postgresql-server-dev-XX


## 2. 编译源码
# https://postgis.net/docs/postgis_installation.html
tar -xvzf postgis-3.4.3dev.tar.gz
# 源码位置
cd postgis-3.4.3dev

# 2.1 配置 pg_config 路径，指定 postgresql 的安装位置
./configure --with-pgconfig=/usr/local/pgsql/bin/pg_config

# 2.2 make
make
# 2.3 扩展位置
sudo make EXTENSIONDIR=/usr/local/pgsql/share/extension/ install

```

以上安装完成后，我们可以在 `postgresql` 数据库中创建 `postgis` 扩展。

## 2. 创建 `postgis` 扩展

验证 `postgis` 扩展是否安装成功。

```sql
create extension postgis;
```
