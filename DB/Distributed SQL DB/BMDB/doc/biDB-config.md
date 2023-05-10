# 1. 配置命令

```bash
# master.conf:
--master_addresses=192.168.50.247:7100,192.168.50.193:7100,192.168.50.236:7100     # 分布式 master IP 地址
--rpc_bind_addresses=192.168.50.236:7100                                           # 本机 IP
--fs_data_dirs=/home/bigmath/disk1
--replication_factor=3

# tserver.conf:
--tserver_master_addrs=192.168.50.247:7100,192.168.50.193:7100,192.168.50.236:7100   # /分布式 master IP 地址
--rpc_bind_addresses=192.168.50.236:9100                                             # 本机 IP
--enable_ysql
--pgsql_proxy_bind_address=0.0.0.0:5433
--cql_proxy_bind_address=0.0.0.0:9042
--fs_data_dirs=/home/bigmath/disk1
# 开启密码认证
--bsql_enable_auth=true

# 运行命令
./bi-master --flagfile master.conf >& /home/bigmath/disk1/yb-master.out &
./bi-tserver --flagfile tserver.conf >& /home/bigmath/disk1/yb-tserver.out &


# 扩容 Master 节点
# 1. 设置环境变量，ADDRS 保存集群中已存在的 Master 节点信息
export ADDRS=192.168.50.249:7100,192.168.50.81:7100,192.168.50.152:7100

# 2. 通过 bi-admin 增加 Master 节点，新增节点为：192.168.50.155 7100
./bi-admin -master_addresses $ADDRS change_master_config ADD_SERVER 192.168.50.155 7100

./bi-admin -master_addresses $ADDRS list_all_masters
Master UUID    RPC Host/Port         State     Role  Broadcast Host/Port 
...         192.168.50.249:7100     ALIVE     LEADER    N/A                 
...         192.168.50.81:7100      ALIVE     FOLLOWER  N/A                 
...         192.168.50.152:7100     ALIVE     FOLLOWER  N/A                 
...         192.168.50.155:7100     ALIVE     FOLLOWER  N/A   


./bi-admin -master_addresses $ADDRS list_all_tablet_servers
Tablet Server UUID    RPC Host/Port     Heartbeat delay    Status   Reads/s  Writes/s 
    ...           192.168.50.155:9100     182.07s         DEAD     0.00     0.00    
    ...           192.168.50.249:9100     0.94s           ALIVE     0.00     0.00     
    ...           192.168.50.152:9100     0.94s           ALIVE     0.00     0.00     
    ...           192.168.50.81:9100      0.94s           ALIVE     0.00     0.00


bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bi-admin -master_addresses $ADDRS change_master_config REMOVE_SERVER 192.168.50.155 7100
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bi-admin -master_addresses $ADDRS list_all_masters
Master UUID    RPC Host/Port         State     Role  Broadcast Host/Port 
    ...      192.168.50.249:7100   ALIVE     LEADER     N/A                 
    ...      192.168.50.81:7100    ALIVE     FOLLOWER   N/A                 
    ...      192.168.50.152:7100   ALIVE     FOLLOWER   N/A    
```
