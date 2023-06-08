# 1. 配置命令

```bash
# master.conf:
--master_addresses=ip1:7100,ip2:7100,ip3:7100     # 分布式 master IP 地址
--rpc_bind_addresses=ip:7100                      # 本机 IP
--fs_data_dirs=/home/bigmath/disk1
--replication_factor=3

# tserver.conf:
--tserver_master_addrs=ip1:7100,ip2:7100,ip3:7100   # 分布式 master IP 地址
--rpc_bind_addresses=ip:9100                        # 本机 IP
--enable_bsql
--pgsql_proxy_bind_address=0.0.0.0:5433
--cql_proxy_bind_address=0.0.0.0:9042
--fs_data_dirs=/home/bigmath/disk1
# 开启密码认证
--bsql_enable_auth=true

# 运行命令
nohup ./bm-master --flagfile master.conf >& /home/bigmath/disk1/bm-master.out &
nohup ./bm-tserver --flagfile tserver.conf >& /home/bigmath/disk1/bm-tserver.out &


# 扩容 Master 节点
# 1. 设置环境变量，ADDRS 保存集群中已存在的 Master 节点信息
export ADDRS=ip1:7100,ip2:7100,ip3:7100

# 2. 通过 bi-admin 增加 Master 节点，新增节点为：127.0.0.1 7100
./bi-admin -master_addresses $ADDRS change_master_config ADD_SERVER 127.0.0.1 7100

./bi-admin -master_addresses $ADDRS list_all_masters
Master UUID    RPC Host/Port         State     Role  Broadcast Host/Port 
...             ip1:7100            ALIVE     LEADER    N/A                 
...             ip2:7100            ALIVE     FOLLOWER  N/A                 
...             ip3:7100            ALIVE     FOLLOWER  N/A                 
...             ip4:7100            ALIVE     FOLLOWER  N/A   


./bi-admin -master_addresses $ADDRS list_all_tablet_servers
Tablet Server UUID    RPC Host/Port     Heartbeat delay    Status   Reads/s  Writes/s 
    ...                 ip1:9100        182.07s             DEAD      0.00     0.00    
    ...                 ip2:9100        0.94s               ALIVE     0.00     0.00     
    ...                 ip3:9100        0.94s               ALIVE     0.00     0.00     
    ...                 ip4:9100        0.94s               ALIVE     0.00     0.00


bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bm-admin -master_addresses $ADDRS change_master_config REMOVE_SERVER 192.168.50.155 7100
bigmath@bigmath-virtual-machine:~/biginsights-0.1/bin$ ./bm-admin -master_addresses $ADDRS list_all_masters
Master UUID    RPC Host/Port         State     Role  Broadcast Host/Port 
    ...         ip1:7100            ALIVE     LEADER     N/A                 
    ...         ip2:7100            ALIVE     FOLLOWER   N/A                 
    ...         ip3:7100            ALIVE     FOLLOWER   N/A    
```
