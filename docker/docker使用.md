
# 1. 命令

```bash
# 查看镜像
docker images

# 查看容器
docker ps -a
```

# 2. 新建容器并共享宿主主机的文件夹

```bash
# -h: 指定主机名，-v: 指定主机的目录 /aaa 映射到 容器中的目录 /BBB
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
