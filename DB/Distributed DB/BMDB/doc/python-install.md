
# Ubuntu config python version

# 1. install python2 & python3

```bash
# install py2
sudo apt-get install python-pip
# install py3
sudo apt install python-is-python3
```

# 2. config python version

```bash
# 移除 /usr/bin/python2 配置项
sudo update-alternatives --remove python /usr/bin/python2


# 安装 /usr/bin/python3 配置，参数 10：表示优先级，数字越大，优先级越高

sudo update-alternatives --install /usr/bin/python python /usr/bin/python3 10

# 配置 python 版本
$ sudo update-alternatives --config python
There are 2 choices for the alternative python (providing /usr/bin/python).

  Selection    Path              Priority   Status
------------------------------------------------------------
  0            /usr/bin/python3   2         auto mode
* 1            /usr/bin/python2   1         manual mode
  2            /usr/bin/python3   2         manual mode

Press <enter> to keep the current choice[*], or type selection number: 


```

./bi-ctl add_node --tserver_flags '"--tserver_master_addrs=192.168.50.249:7100,192.168.50.81:7100,192.168.50.152:7100,192.168.50.155:7100", "--rpc_bind_addresses=192.168.50.155:9100", "--enable_ysql", "--pgsql_proxy_bind_address=0.0.0.0:5433", "--cql_proxy_bind_address=0.0.0.0:9042", "--fs_data_dirs=/home/bigmath/disk1", "--bsql_enable_auth=true"'


--tserver_master_addrs=192.168.50.249:7100,192.168.50.81:7100,192.168.50.152:7100,192.168.50.155:7100
--rpc_bind_addresses=192.168.50.155:9100
--enable_ysql
--pgsql_proxy_bind_address=0.0.0.0:5433
--cql_proxy_bind_address=0.0.0.0:9042
--fs_data_dirs=/home/bigmath/disk1
--bsql_enable_auth=true
