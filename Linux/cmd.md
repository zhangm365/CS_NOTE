
# `Linux` 常见命令

# 1. 将终端输出内容重定向到文件

```bash
# >&: 表示将标准输出和标出错误重定向到 file 文件，最后的 &: 表示当前命令以后台的方式执行
cmd >& file &
```

但是在 `.sh` 文件需要修改为以下格式：

```bash
> file 2>&1 &
```

例如以下程序：

```bash
#!/bin/sh
#
# D2GS
#
# Go to the directory
cd ~

# Run the applications, 
if ! ps aux | pgrep "D2GS"; then
    wine "C:/D2GS/D2GS.exe" > /dev/null 2>&1 &  # 在 .sh 文件这样写
fi

```

# 2. ubuntu 修改镜像源

Ubuntu 的软件源配置文件是 `/etc/apt/sources.list`。将系统自带的该文件做个备份，将该文件替换为下面内容，即可使用选择的软件源镜像。

修改源：

```shell
# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse

# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-security main restricted universe multiverse
# # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-security main restricted universe multiverse

deb http://security.ubuntu.com/ubuntu/ jammy-security main restricted universe multiverse
# deb-src http://security.ubuntu.com/ubuntu/ jammy-security main restricted universe multiverse

```

写入文件：

```shell
# tee -a : 追加方式写入。> /dev/null：将写入信息不输出到终端上。
echo "deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy main restricted universe multiverse" | sudo tee -a /etc/apt/sources.list > /dev/null
echo "deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse" | sudo tee -a /etc/apt/sources.list > /dev/null
echo "deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse" | sudo tee -a /etc/apt/sources.list > /dev/null
echo "deb http://security.ubuntu.com/ubuntu/ jammy-security main restricted universe multiverse" | sudo tee -a /etc/apt/sources.list > /dev/null
```

# 3. 终止进程

```shell
# 根据进程名搜索 process_name，并杀死对应的进程
kill $(ps aux | grep 'process_name' | awk '{print $2}')
```
