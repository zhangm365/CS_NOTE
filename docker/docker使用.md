
# 1. 命令

```bash
# 查看镜像
docker images

# 查看容器
docker ps -a
```

# 2. 新建容器并共享宿主主机的文件夹

```bash
# -h: 指定主机名，-v: 指定主机的目录 /aaa 映射到容器中的目录 /BBB
docker run --name ubuntu-name -ti -h "ubuntu" -v /AAA:/BBB -p 80:80 -d ubuntu

# docker 内使用 gdb 调试：需要加 "--cap-add=SYS_PTRACE --security-opt seccomp=unconfined"
docker run --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -p 80:80 -v /Users/zhangmao/github/MicroWebServer:/Users/zhangmao/github/MicroWebServer --name ubuntu -dti ubuntu:20.04
```

```bash
# 修改清华镜像源：https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu-ports/
# ubuntu 20.04: focal | ubuntu 22.04: jammy
# lsb_release -a 查看版本
echo "
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

# 预发布软件源，不建议启用
# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-proposed main restricted universe multiverse
# # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-proposed main restricted universe multiverse
" > /etc/apt/sources.list
```

# 3. 运行 Docker

```bash
docker exec -it ubuntu-name /bin/bash
```

# 4. 导出容器到镜像

```bash
# -m: 提交的描述信息，-a: 指定镜像作者，ubuntu-name: 容器名，ubuntu:22.04: 镜像名
docker commit -m "ubuntu" -a "zhangmao" ubuntu-name ubuntu:22.04
```

# 5. docker 服务

[`SysVInit`](https://wiki.archlinux.org/title/SysVinit) 是 `Linux` 中的经典初始化过程。初始化过程依赖于各个服务在 `/etc/init.d` 目录中安装相关脚本。此外，脚本还必须支持 `start`、`stop` 和 `status` 等标准命令。该启动系统的一个主要特点是，它是一个一次性启动进程，不会在启动后跟踪各个服务。`service` 命令用于从终端运行这些启动脚本。

[`SystemD`](https://man7.org/linux/man-pages/man1/systemd.1.html) 是一种最新的初始化系统，旨在取代 `SysVInit`。事实上，大多数 Linux 发行版（如 Debian 和 Red Hat）都已将 `SystemD` 作为开箱即用的初始化系统。与 `SysVInit` 不同的是，`SystemD` 在初始化完成后会继续作为守护进程运行。此外，它们还通过 `cgroups` 积极跟踪服务。`systemctl` 命令是用户交互和配置 `SystemD` 的入口。

```bash
sudo systemctl start docker
# sudo service docker start

sudo systemctl restart docker 
# sudo service docker restart

sudo systemctl status docker
# sudo service docker status

sudo systemctl stop docker
# sudo service docker stop

# Warning: Stopping docker.service, but it can still be activated by:
#  docker.socket
sudo systemctl stop docker.socket
sudo systemctl status docker.socket
```
