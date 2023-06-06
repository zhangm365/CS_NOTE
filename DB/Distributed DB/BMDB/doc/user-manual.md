
# 1. 扩缩容

BMDB 的扩缩容是指根据实际需求在不中断在线服务的情况下，动态调整分布式集群的规模以满足数据存储和计算分析的处理。在分布式数据库系统中，扩缩容通常需要涉及到多个节点之间的协调和数据迁移备份等。下面是一些常见的扩缩容策略：

- 垂直扩展：增加单个节点的计算和存储资源，例如增加 CPU、内存、磁盘等硬件资源，以提升集群的整体性能。但这种扩容方式成本较高且不能无限制地扩展。
- 水平扩展：通过增加节点数量来弹性扩展系统的计算和存储资源。这种扩容方式可以提供更好的扩展性，但需要在增加节点的同时需要采用分片、副本等技术来保证数据的高可用性和强一致性。
- 自动化扩缩容：利用自动化工具和算法来监测系统的负载和性能，自动调整节点数量和配置来实现扩缩容。这种扩容方式可以提供更高的效率和精确度，但需要谨慎设计和测试算法，以避免误判和误操作。

以下是通过水平扩展的策略介绍扩容/缩容分布式集群中 Master、TServer 节点的具体操作步骤。

## 1.1 扩容 `Master` 节点

例如，分布式集群原拓扑结构如下：
|  主机 IP  | 节点类型  |
|  :------:  | :------:  |
| 10.0.0.1  | Master |
| 10.0.0.2  | Master |
| 10.0.0.3  | Master |

### 1.1.1 配置命令

如果要在集群中增加一个 `Master` 节点，`IP` 地址为 `10.0.0.4`，在节点的当前目录 `~/biginsights-0.1/bin` 请按以下步骤执行命令：

```bash

# 1. 启动 `bm-master` 进程并配置参数 `rpc_bind_addresses` 和 `fs_data_dirs`
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bm-master --rpc_bind_addresses=10.0.0.4:7100 --fs_data_dirs=/home/bigmath/disk1 >& /home/bigmath/disk1/bm-master.out & 

# 2. 添加环境变量 ADDRS
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ export ADDRS=10.0.0.1:7100,10.0.0.2:7100,10.0.0.3:7100

# 查看环境变量设置是否成功
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ echo $ADDRS
10.0.0.1:7100,10.0.0.2:7100,10.0.0.3:7100

# 3. 使用 ./bm-admin 命令查看扩容前的 Master 节点状态信息
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bm-admin -master_addresses $ADDRS list_all_masters

Master UUID    RPC Host/Port        State       Role         Broadcast Host/Port 
   ...          10.0.0.1:7100        ALIVE     LEADER         N/A                 
   ...          10.0.0.2:7100        ALIVE     FOLLOWER     N/A                 
   ...          10.0.0.3:7100        ALIVE     FOLLOWER     N/A    

# 4. 运行 ./bm-admin 命令增加 Master 节点
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bm-admin -master_addresses $ADDRS change_master_config ADD_SERVER 10.0.0.4 7100

# 5. 查看扩容后 Master 节点状态：可以看到新增节点的信息
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bm-admin -master_addresses $ADDRS list_all_masters

Master UUID    RPC Host/Port        State       Role         Broadcast Host/Port 
   ...          10.0.0.1:7100        ALIVE     LEADER         N/A                 
   ...          10.0.0.2:7100        ALIVE     FOLLOWER       N/A                 
   ...          10.0.0.3:7100        ALIVE     FOLLOWER       N/A                 
   ...          10.0.0.4:7100        ALIVE     FOLLOWER       N/A  

```

打开浏览器访问监控平台：[http://10.0.0.4:7000](http://10.0.0.4:7000/)，查看新增节点是否启动成功和当前集群的运行状态。

## 1.2 扩容 `TServer` 节点

例如，分布式集群原拓扑结构如下：

|  主机 IP  | 节点类型  |
|  :------:  | :------:  |
| 10.0.0.1  | TServer |
| 10.0.0.2  | TServer |
| 10.0.0.3  | TServer |

### 1.2.1 配置命令

如果要增加一个 `TServer` 节点，`IP` 地址为 `10.0.0.4`，在当前目录 `~/biginsights-0.1/bin` 中创建 `tserver.conf` 配置文件：

```bash
# 1. 在 /biginsights-0.1/bin/ 目录创建 tserver.conf 文件
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ touch tserver.conf 

# 2. 打开 tserver.conf 文件，增加新节点的配置 10.0.0.4:7100
--tserver_master_addrs=10.0.0.1:7100,10.0.0.2:7100,10.0.0.3:7100,10.0.0.4:7100    # 指定所有分布式 master IP 地址
--rpc_bind_addresses=10.0.0.4:9100    # 绑定本机 IP
--enable_ysql    # 使能支持 BSQL API，默认值是 true。需要和 master 节点中的配置一致
--pgsql_proxy_bind_address=0.0.0.0:5433    # 指定 BSQL API 的 TCP/IP 绑定地址。默认值 0.0.0.0:5433 表示监听所有 IPV4 地址访问 localhost 上的端口 5433。
--cql_proxy_bind_address=0.0.0.0:9042    # 指定 YCQL API 的绑定地址
--fs_data_dirs=/home/bigmath/disk1    # 数据挂载目录
--bsql_enable_auth=true    # 开启身份认证，需要验证密码才可以登录数据库

# 3. 运行 ./bm-admin 命令查看扩容前 TServer 节点状态  
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bm-admin -master_addresses $ADDRS list_all_tablet_servers

Tablet Server UUID    RPC Host/Port     Heartbeat delay    Status   Reads/s  Writes/s 
      ...            10.0.0.3::9100        0.19s         ALIVE     0.00     0.00     
      ...            10.0.0.1::9100        0.15s         ALIVE     0.00     0.00     
      ...            10.0.0.2::9100        0.19s         ALIVE     0.00     0.00

# 4. 运行 ./bm-tserver 命令加载配置文件，扩容 tserver 节点
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bm-tserver --flagfile tserver.conf >& /home/bigmath/disk1/yb-tserver.out &


# 5. 运行 ./bm-admin 命令查看扩容后 TServer 节点状态  
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bm-admin -master_addresses $ADDRS list_all_tablet_servers

Tablet Server UUID    RPC Host/Port     Heartbeat delay    Status   Reads/s  Writes/s 
      ...            10.0.0.4::9100        0.19s         ALIVE     0.00     0.00    
      ...            10.0.0.3::9100        0.19s         ALIVE     0.00     0.00     
      ...            10.0.0.1::9100        0.15s         ALIVE     0.00     0.00     
     ...             10.0.0.2::9100        0.19s         ALIVE     0.00     0.00

```

同时，打开浏览器访问监控平台：[http://10.0.0.4:9000](http://10.0.0.4:9000/)，查看新增节点是否成功启动和集群的运行状态。

## 2. 缩容 `Master` 节点

如果缩容当前集群中 `Master` 节点的规模，可以通过命令 `bm-admin` 进行实现。

### 2.1. 配置命令

例如移除 IP 地址为 `10.0.0.4` 的节点：

```bash

# 1. 运行 ./bm-admin 命令指定参数 REMOVE_SERVER 缩容 Master 节点，
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bi-admin -master_addresses $ADDRS change_master_config REMOVE_SERVER 10.0.0.4 7100
# 2. 查看 Master 节点状态，10.0.0.4 节点已退出集群
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bi-admin -master_addresses $ADDRS list_all_masters
Master UUID    RPC Host/Port     State        Role     Broadcast Host/Port 
    ...         10.0.0.1:7100      ALIVE     LEADER      N/A                 
    ...         10.0.0.2:7100      ALIVE     FOLLOWER    N/A                 
    ...         10.0.0.3:7100      ALIVE     FOLLOWER    N/A  

# 3. 同时，终止 bm-master 进程
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ps aux | grep bm-
bigmath   150835  0.4  0.5 452432 85344 pts/1    Sl   4月27  46:32 ./bm-master --rpc_bind_addresses=10.0.0.0:4 --fs_data_dirs=/home/bigmath/disk1

# 4. 终止 bm-master 进程
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ kill -9 150835
```

如上，是缩容 `Master` 节点的步骤操作。

## 3. 缩容 `TServer` 节点

缩容 `TServer` 节点是通过终止 `bm-tserver` 进程实现的。

### 3.1. 配置命令

例如，缩容 IP 地址是 `10.0.0.4` 的节点，终止对应的进程：

```bash

# 查看 TServer 节点进程状态
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ps aux | grep bm-
bigmath    28788  279  2.1 1127792 349304 pts/0  Sl   19:57   0:19 ./bm-tserver --flagfile tserver.conf

# 终止 bi-tserver 进程
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ kill -9 28788

# 查看进程已终止
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ps aux | grep bi-
bigmath    29126  0.0  0.0  17864  2684 pts/0    S+   20:08   0:00 grep --color=auto bi-

# 运行 ./bm-admin 命令查看 TServer 节点状态：10.0.0.4 节点已停止服务  
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bm-admin -master_addresses $ADDRS list_all_tablet_servers

Tablet Server UUID    RPC Host/Port     Heartbeat delay    Status   Reads/s  Writes/s 
      ...              10.0.0.4::9100        182.07s         DEAD     0.00     0.00    
      ...              10.0.0.3::9100        0.94s           ALIVE    0.00     0.00     
      ...              10.0.0.1::9100        0.94s           ALIVE    0.00     0.00     
      ...              10.0.0.2::9100        0.94s           ALIVE    0.00     0.00  


```

现在打开浏览器访问监控平台：[http://10.0.0.4:7000](http://10.0.0.4:7000/) 和 [http://10.0.0.4:9000](http://10.0.0.4:9000/)，是无法访问的。

# 3. SQL 基础操作（Cassandra）

Apache Cassandra 是一个开源、高可用和可扩展的 NoSQL 分布式数据库，它支持对海量数据进行快速地组织和分析等。本节内容安排如下：

- 连接数据库；
- DDL(Data Definition Language)：数据定义语言，用于定义数据库对象，包括库、表、索引等，以及用户的权限等；
- DML(Data Manipulation Language)：数据操作语言，用于操作和业务相关的记录；
- 表达式：一个或多个条件值、运算符、函数等组合的有限表达式；
- 用户自定义数据类型：除数据库内置数据类型外，支持用户自定义新的数据类型。

## 3.1 连接数据库

`bcqlsh` 是一个使用 `CQL(Cassandra Query Language)` 与 `Cassandra` 数据库交互的命令行工具，它位于 `~/biginsights-0.1/bin` 目录，以下是通过该命令连接数据库的示例：

```bash
# 运行 bcqlsh 命令
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bcqlsh
```

```sql
Connected to local cluster at 127.0.0.1:9042.
[bcqlsh 5.0.1 | Cassandra 3.9-SNAPSHOT | CQL spec 3.4.2 | Native protocol v4]
Use HELP for help.
/* 查看所有的键空间，确认连接成功。*/
bcqlsh> describe keyspaces;

system_schema  system_auth  system
```

## 3.2 创建、查看和删除键空间

键空间是一组数据库对象的集合。

```sql
/* 创建一个名为 cas_db 的键空间，没有错误输出表示创建成功 */
bcqlsh> create keyspace cas_db;
/* 查看键空间 */
bcqlsh> desc keyspaces;

system_schema  system_auth  system  cas_db

/* 查看 cas_db 的具体信息 */
bcqlsh> desc cas_db;

CREATE KEYSPACE cas_db WITH replication = {'class': 'SimpleStrategy', 'replication_factor': '3'}  AND durable_writes = true;

/* 使用名为 cas_db 的键空间 */
bcqlsh> use cas_db;
bcqlsh:cas_db> 
bcqlsh:cas_db> desc tables;

<empty>

/* 删除键空间：需要注意的是当键空间包含表时，需要先删除全部表才能删除键空间。*/
bcqlsh> drop keyspace cas_db;

/* 查看是否删除成功 */
bcqlsh> desc keyspaces;

system_schema  system_auth  system

```

## 3.3 创建、查看和删除表

创建表需要在指定的键空间进行操作。

```sql
/* 在键空间 cas_db 中创建一个名为 stock_market 的表 */
bcqlsh> create table cas_db.stock_market(
    stock_symbol text,    /* 股票代码 */ 
    ts text,    /* timestamp */
    cur_price float,    /* 股票价格 */
    primary key(stock_symbol, ts));    /* 主键 */

/* 查看表的信息 */
bcqlsh> desc cas_db.stock_market;

CREATE TABLE cas_db.stock_market (
    stock_symbol text,
    ts text,
    cur_price float,
    PRIMARY KEY (stock_symbol, ts)
) WITH CLUSTERING ORDER BY (ts ASC)
    AND default_time_to_live = 0
    AND transactions = {'enabled': 'false'};

/* 使用 select 语句查询表数据 */
bcqlsh> select * from cas_db.stock_market ;

 stock_symbol | ts | cur_price
--------------+----+-----------

(0 rows)

/* 删除表 */
bcqlsh> drop table cas_db.stock_market;
```

## 3.4 操作记录

- 使用 `INSERT` 向表内插入记录。

```sql
/* 插入两条记录 */
bcqlsh> INSERT INTO cas_db.stock_market (stock_symbol,ts,cur_price) VALUES ('AAPL','2017-10-26 09:00:00',157.41);
bcqlsh> INSERT INTO cas_db.stock_market (stock_symbol,ts,cur_price) VALUES ('AAPL','2017-10-26 10:00:00',157);
/* 查询 */
bcqlsh:cas_db> select * from stock_market ;

 stock_symbol | ts                  | cur_price
--------------+---------------------+-----------
         AAPL | 2017-10-26 09:00:00 |    157.41
         AAPL | 2017-10-26 10:00:00 |       157
```

- 使用 `UPDATE` 更新某行记录。
  
```sql
bcqlsh:cas_db> UPDATE stock_market set cur_price = 158.1 where stock_symbol = 'AAPL' and ts = '2017-10-26 10:00:00';
/* 查看是否修改成功 */
bcqlsh:cas_db> select cur_price from stock_market where stock_symbol = 'AAPL' and ts = '2017-10-26 10:00:00';

 cur_price
-----------
 158.10001

```

- 使用 `DELETE` 删除某行记录

```sql
bcqlsh:cas_db> DELETE from stock_market where stock_symbol = 'AAPL' and ts = '2017-10-26 10:00:00';
bcqlsh:cas_db> select * from stock_market ;

 stock_symbol | ts                  | cur_price
--------------+---------------------+-----------
         AAPL | 2017-10-26 09:00:00 |    157.41

(1 rows)

```

- 使用 `SELECT` 查询表内记录。

```sql
/* 查找某列数据 */
bcqlsh:cas_db> SELECT stock_symbol from stock_market ;

 stock_symbol
--------------
         AAPL

(1 rows)
```

## 3.5 自定义数据类型

可以使用 `CREATE TYPE` 在键空间创建一个自定义的数据类型。

```sql
/* 创建新的类型 person */
bcqlsh:cas_db> CREATE TYPE person(first_name TEXT, last_name TEXT, emails FROZEN<LIST<TEXT>>);

/* 查看 */
bcqlsh:cas_db> desc type person;

CREATE TYPE cas_db.person (
    first_name text,
    last_name text,
    emails frozen<list<text>>
);
/* 使用新创建的类型定义 employee 变量 */
bcqlsh:cas_db> CREATE TABLE employees(employee_id INT PRIMARY KEY, employee person);
/* 创建表 */
bcqlsh:cas_db> CREATE TABLE employees(employee_id INT PRIMARY KEY, employee person);
/* 插入数据 */
bcqlsh:cas_db> INSERT INTO employees(employee_id, employee)
                   VALUES (1, {first_name : 'John', last_name : 'Doe', emails : ['jdoe@example.com']});

/* 查询数据 */
bcqlsh:cas_db> SELECT * FROM employees ;

 employee_id | employee
-------------+----------------------------------------------------------------------
           1 | {first_name: 'John', last_name: 'Doe', emails: ['jdoe@example.com']}

(1 rows)
bcqlsh:cas_db>

```

# 4. 性能优化

数据库的性能优化是指通过改进数据库系统的各种组件和技术，以使其在满足用户需求的同时，提高其数据处理性能的过程。

## 4.1. 性能概述

本节介绍数据库性能优化的一些基本概念，包括响应时间、吞吐量和资源利用率等，以及性能优化的基本过程。

### 4.1.1. 响应时间与数据库时间

- 响应时间：指业务请求从发起到结果返回所消耗的时间。

一个典型的用户请求的处理时序图如下，它包括用户与应用系统的网络延迟、应用系统的处理时间、应用系统和数据库的网络延迟以及数据库的服务时间等。

![响应时间](./draw_pics/request_time.png "响应时序图")

因此，一个用户的响应时间会受到请求链路上的各个子系统的影响，比如网络延迟、系统的吞吐量和并发能力、CPU 和内存和磁盘 IO 的资源利用率等。要想对整个系统进行性能优化，需要综合考量和权衡上述各个指标的影响大小，从而有效地定位性能问题。

- 数据库时间：数据库执行用户请求的所需时间。
在指定时间范围内 ($\Delta$T) 的数据库时间的计算方式为数据库并发处理所有应用请求的时间总和。
它可以采用如下的计算方式：

方法一：QPS 乘以平均时延比乘以 $\Delta$T：Total Time =  QPS $\times$ latency% $\times$ $\Delta$T；
> latency 通常的取值是 95。

### 4.1.2. 系统吞吐量

吞吐量是指一定时间内，系统可以完成的任务数量。在数据库中，它用来表示数据库能够处理的查询请求数。

因此，通常情况下，系统吞吐量越高，用户的响应时间就越短。然而，当系统的吞吐量不断增加时，系统的资源利用率上升，用户请求的排队时延也会随之增加，那么系统的负载压力可能也会不断增加。

### 4.1.3 性能优化的流程

性能优化流程通常分为以下几个步骤：

1. 定义目标；
2. 分析性能数据；
3. 制定优化方案；
4. 实施优化方案；
5. 测试和评估；
6. 监控和维护；

总之，数据库性能优化需要系统化、全面化的方法，通过动态循环第 2 - 6 步骤，不断地优化系统的各个方面，以达到提高系统性能和稳定性的目的。

#### 4.1.3.1 定义目标

不同数据库系统的优化目标是不同的，首先需要明确优化的目标是什么，例如对于 OLTP 负载的数据库，优化目标是尽可能降低批量交易的长尾延迟，一个好的目标应该是可以量化且可行的：

- 在金融交易系统中，业务高峰期的某个时间点，支付交易的长尾延迟应该是小于 100ms；

#### 4.1.3.2 分析性能数据

将性能监控和日志分析工具收集到的数据指标进行着重分析，找出系统的瓶颈和优化点，确定需要优化的方向和措施。

通常可以监控的指标如下：

- 平均响应时间和网络延迟时间；
- CPU 利用率；
- 内存占用率；
- 磁盘 I/O；
- QPS、TPS、Latency(95%) 数据库参数等

#### 4.1.3.3 制定优化方案

根据分析结果，制定相应的优化方案。通常，数据库系统内部会详细记录 Query 延迟和请求处理数等，因此，基于数据库慢日志文件，可以判断性能瓶颈是否为数据库的原因。

若瓶颈在数据库方面，可以考虑进行数据库的设计优化、索引优化、查询优化、缓存优化、数据库分区、负载均衡等操作。

当成功确定系统瓶颈点之后，根据当前的实际情况提出合理可行、低成本低风险和尽可能获得最大收益的方案。例如：

- 系统资源过载的情况下，可以考虑扩容分布式集群中的节点，但应考虑实际的成本和风险等问题；
- 若是某个业务模块的执行语句导致的延迟，那么可考虑从数据库本身的缺点和执行语句方面着手优化等。

#### 4.1.3.4 实施优化方案

综合考量所制定优化方案的风险、收益和成本等因素，逐步将优化方案实施到生产环境中，如增加索引、重构 SQL 查询语句、增加缓存、调整系统配置等。

#### 4.1.3.5 测试与评估

在实施优化方案之后，需要对系统进行相应的测试和评估，确保是否达到了优化目标，如提高系统的响应速度等。

#### 4.1.3.6 监控与维护

性能优化是一个持续不断的过程，需要对系统进行持续的监控和维护，及时发现和解决问题，保持系统的高性能和稳定性。
