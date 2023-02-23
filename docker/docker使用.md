
# 查看镜像

```bash
docker images
```

# 运行 Docker

```bash

docker exec -it ubuntu-name /bin/bash

```

# 新建容器并共享宿主主机的文件夹
```bash
# -v 指定主机的目录/aaa 和 docker容器路径/BBB
docker run --name ubuntu-name -ti -v /AAA:/BBB -d -p 3316:22 ubuntu
```

```bash
# 修改清华镜像源：https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu-ports/

echo "
# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ focal main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ focal main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ focal-updates main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ focal-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ focal-backports main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ focal-backports main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ focal-security main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ focal-security main restricted universe multiverse
" >> /etc/apt/sources.list
```