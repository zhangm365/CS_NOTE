
# 1. 测试工具

## 1.1 `sysbench` 测试工具

```bash
# 安装
sudo apt install sysbench
```

### 1.1.1 `cpu` 性能测试

使用质数相加的用例进行测试。

```bash
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ sysbench cpu help
sysbench 1.0.20 (using system LuaJIT 2.1.0-beta3)

cpu options:
  --cpu-max-prime=N upper limit for primes generator [10000]
```

```bash
# 1.cleanup: 表示删除测试文件。如果报错可以尝试更换端口号。 
sysbench /usr/share/sysbench/oltp_read_write.lua --db-driver=pgsql --pgsql-host=127.0.0.1 --pgsql-port=5433 --pgsql-user=postgres --pgsql-password=postgres --pgsql-db=postgres --tables=18 --table-size=1000000 --report-interval=10 --threads=64 --time=600 cleanup


# 2.prepare: 生成测试文件
sysbench /usr/share/sysbench/oltp_read_write.lua --db-driver=pgsql --pgsql-host=127.0.0.1 --pgsql-port=5433 --pgsql-user=postgres --pgsql-password=postgres --pgsql-db=postgres --tables=18 --table-size=1000000 --report-interval=10 --threads=64 --time=600 prepare

# 3.run: 运行
# 测试数据库的综合读写 TPS，使用 oltp_read_write 模式。线程数 64 个，创建 18 个用户表，每个表大小为 1000w 的规模
sysbench /usr/share/sysbench/oltp_read_write.lua --db-driver=pgsql --pgsql-host=127.0.0.1 --pgsql-port=5433 --pgsql-user=postgres --pgsql-password=postgres --pgsql-db=postgres --tables=18 --table-size=1000000 --report-interval=10 --threads=64 --time=600 run

# 在第 600s 时刻输出的压测结果：
[ 600s ] thds: 64 tps: 0.70 qps: 13.50 (r/w/o: 9.30/1.60/2.60) lat (ms,95%): 100000.00 err/s: 0.00 reconn/s: 0.00
# thds:64 : 表示当前有 64 个线程正在压测
# tps:0.70 : 表示当前每秒执行了 0.70 个事务
# qps:13.50: 表示当前每秒可以执行 13.50 个请求
# (r/w/o: 9.30/1.60/2.60) : 表示在每秒 13.50 个请求中，有 9.30 个读请求，1.60 个写请求，2.60 个其他请求，其实就是对 qps 的细化
# lat (ms,95%): 100000.00：表示 95% 的请求的延迟都在 100000.00 毫秒以下
# err/s: 0.00 reconn/s: 0.00：表示有0个请求失败，发生了0次的网络重连

# 最后的结果如下：
SQL statistics:
    queries performed:
        read:                            6502
        write:                           1067
        other:                           1657
        total:                           9226
    transactions:                        451    (0.68 per sec.)
    queries:                             9226   (13.91 per sec.)
    ignored errors:                      16     (0.02 per sec.)
    reconnects:                          0      (0.00 per sec.)

General statistics:
    total time:                          663.3629s
    total number of events:              451

Latency (ms):
         min:                                 8221.23
         avg:                                89591.55
         max:                               267709.61
         95th percentile:                   100000.00
         sum:                             40405789.84

Threads fairness:
    events (avg/stddev):           7.0469/1.28
    execution time (avg/stddev):   631.3405/19.30


```

## 1.2 `benchmarksql` 工具

`benchmarksql` 工具的环境配置

# 1.2.1 安装

1. 下载压缩包，解压使用。链接如下：

<https://sourceforge.net/projects/benchmarksql/>

2. 安装 JAVA 环境

推荐安装 openjdk-11-jdk。

```bash
sudo apt install openjdk-11-jdk

# java 版本
java --version

# output
openjdk 11.0.18 2023-01-17
OpenJDK Runtime Environment (build 11.0.18+10-post-Ubuntu-0ubuntu122.04)
OpenJDK 64-Bit Server VM (build 11.0.18+10-post-Ubuntu-0ubuntu122.04, mixed mode, sharing)
```

3. 安装 R 语言

方便后续生成报告使用，链接：

<https://cran.r-project.org/>

4. pgsql JDBC Driver

<https://jdbc.postgresql.org/>
下载数据库驱动包，复制到 /path/benchmarksql-5.0/lib/postgres 目录下。

### 1.2.2 配置文件

以目前最新的版本 `benchmarksql-5.0` 为例，解压该压缩包后：

```bash
# 解压
unzip benchmarksql-5.0

# 进入根目录，可以查看 HOW-TO-RUN.txt 指南。
cd benchmarksql-5.0/

# 进入 run 目录
cd run
# run 目录中的文件如下：
props.pg    # pgsql conf，根据此文件复制一份自己的配置文件进行测试
cp props.pg my_postgres.properties  # 生成自己的配置文件

# my_postgres.properties 配置文件如下：

runDatabaseBuild.sh my_postgres.properties  # 根据配置文件生成测试数据
runBenchmark.sh my_postgres.properties  # 运行
runDatabaseDestroy.sh my_postgres.properties  # 删除所有测试数据

generateReport.sh my_result_    # 根据 resultDirectory 的值，然后生成 HTML 报告和图片
generateGraphs.sh my_result  # 只生成图片                          

```

## 1.3 在线扩容能力

在数据库系统中，存储节点和计算节点是两个不同的概念。

存储节点是指用于存储数据的节点，通常包括磁盘、存储服务器或存储阵列等硬件设备。存储节点通常具有高速的存储设备和存储协议，例如SAN、NAS或DFS等，可以提供高效的数据存储和访问服务。

计算节点是指用于执行计算任务的节点，通常包括服务器、计算机或计算集群等硬件设备。计算节点通常具有高速的处理器和内存等硬件资源，可以执行复杂的计算任务和查询操作。

在分布式数据库系统中，存储节点和计算节点通常是分开的，存储节点负责存储数据，计算节点负责执行查询和计算任务。计算节点通过网络连接到存储节点，从存储节点中读取数据并执行计算任务，然后将计算结果返回给客户端。

## 1.4 `TPC-H` 数据集

\copy customer from '/home/bigmath/TPC-H V3.0.1/dbgen/tbl/customer.tbl' with delimiter as '|' NULL '';
\copy lineitem from '/home/bigmath/TPC-H V3.0.1/dbgen/tbl/lineitem.tbl' with delimiter as '|' NULL '';
\copy orders from '/home/bigmath/TPC-H V3.0.1/dbgen/tbl/lineitem.tbl' with delimiter as '|' NULL '';
\copy partsupp from '/home/bigmath/TPC-H V3.0.1/dbgen/tbl/customer.tbl' with delimiter as '|' NULL '';
\copy part from '/home/bigmath/TPC-H V3.0.1/dbgen/tbl/customer.tbl' with delimiter as '|' NULL '';
\copy supplier from '/home/bigmath/TPC-H V3.0.1/dbgen/tbl/customer.tbl' with delimiter as '|' NULL '';
\copy nation from '/home/bigmath/TPC-H V3.0.1/dbgen/tbl/customer.tbl' with delimiter as '|' NULL '';
\copy region from '/home/bigmath/TPC-H V3.0.1/dbgen/tbl/customer.tbl' with delimiter as '|' NULL '';

l_orderkey, l_partkey, l_suppkey, l_linenumber, l_quantity, l_extendedprice, l_discount, l_tax, l_returnflag, l_linestatus,
l_shipdate, l_commitdate, l_receiptdate, l_shipinstruct, l_shipmode, l_comment
