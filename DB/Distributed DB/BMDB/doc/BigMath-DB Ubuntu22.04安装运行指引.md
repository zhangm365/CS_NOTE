# BigMath-DB Ubuntu22.04安装运行指引

## 一、搭建环境

### 1. 安装运行环境

```shell
sudo apt update
sudo apt upgrade -y
sudo apt install -y autoconf build-essential curl gettext git \
    locales ninja-build pkg-config rsync libffi-dev python3 python3-dev \
    python3-venv python3-pip cmake openjdk-8-jdk maven ntp
sudo pip install llvm_installer
sudo locale-gen en_US.UTF-8
```

### 2. 配置系统参数

用`ulimit`检查系统参数，

```shellsession
$ ulimit -a
```

各项参数应该如下所示：

```textile
core file size          (blocks, -c) unlimited
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited
pending signals                 (-i) 119934
max locked memory       (kbytes, -l) 64
max memory size         (kbytes, -m) unlimited
open files                      (-n) 1048576
pipe size            (512 bytes, -p) 8
POSIX message queues     (bytes, -q) 819200
real-time priority              (-r) 0
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) 12000
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited
```

如果不是，编辑`/etc/security/limits.conf`

```textile
*                -       core            unlimited
*                -       data            unlimited
*                -       fsize           unlimited
*                -       sigpending      119934
*                -       memlock         64
*                -       rss             unlimited
*                -       nofile          1048576
*                -       msgqueue        819200
*                -       stack           8192
*                -       cpu             unlimited
*                -       nproc           12000
*                -       locks           unlimited
```

## 二、下载BigMath-DB代码

### 1. 设置gitlab的ssh key

如果没有配置gitlab上的ssh key，下载代码时会碰到以下错误：

```shell
$ git clone git@gitlab.bigmath.com:rd/bigmath-db.git
Cloning into 'biginsights'...
The authenticity of host 'gitlab.bigmath.com (192.168.2.200)' can't be established.
ED25519 key fingerprint is SHA256:aKOaQwF28bMAQUC+9/yx221d2RQ3sUqVthc9UZejxYQ.
This key is not known by any other names
Are you sure you want to continue connecting (yes/no/[fingerprint])? 
Host key verification failed.
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
```

需要安装与gitlab同步的ssh key：

```shell
$ cd ~/.ssh/    #回到用户目录下面的.ssh目录
$ ssh-keygen -t ed25519 -C "<comment>" #生成key对，会有如下打印,如果遇到需要输入，回车即可
Generating public/private ed25519 key pair.
Enter file in which to save the key (/home/xys/.ssh/id_ed25519): 
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in /home/xys/.ssh/id_ed25519
Your public key has been saved in /home/xys/.ssh/id_ed25519.pub
The key fingerprint is:
SHA256:C+1tMd3CjZ0k4vCeHdoYY3MBDM58aJBdd0V1nznhlbI <comment>
The key's randomart image is:
+--[ED25519 256]--+
|      .o.+o . .+O|
|      .=...o o..B|
|        B o o +=.|
|       o = + E ..|
|      . S X B =  |
|       o = & o   |
|        o B o    |
|         .       |
|                 |
+----[SHA256]-----+
$ ls #生成如下两个文件
id_ed25519  id_ed25519.pub
$ cat id_ed25519.pub #查看key的值，下面的值需要复制到gitlab上，具体操作下一小结
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIJN1wvqPMXRLPjn9KrcF/mE8zU8b8Z38g22NMGdIZp/U <comment>
```

### 2. gitlab同步ssh key

进入网址：`https://gitlab.bigmath.com/-/profile/keys`，按如下操作：
注意：上图key输入栏里面的内容就是上面过程中ssh key的内容。

<img title="" src="file:///d:/Users/admin/Documents/addsshkey1.png" alt="" width="691">

### 3. 下载代码

<mark>代码必须位于`/home/bigmath/code`下面</mark>，用户名同样建议用bigmath

```shell
$ cd
$ mkdir code
$ git clone git@gitlab.bigmath.com:rd/bigmath-db.git  
#此命令执行的时候可能会失败，多执行几次
```

## 三、编译代码

将第三方库拷贝至本机目录`/home/bigmath/tmp_work`

```shell
$ cd
$ mkdir tmp_work
$ scp bigmath@192.168.50.150:~/tmp_work/bigmath-thirdparty.tar.gz ~/tmp_work/
# 文件较大，拷贝需要一点时间
$ tar -xvf bigmath-thirdparty-clang15.tar.gz
```

建立`/opt/bm-build`目录及设置环境变量

```shell
$ sudo mkdir /opt/bm-build
$ sudo chown bigmath /opt/bm-build
$ export BM_THIRDPARTY_DIR=~/tmp_work/bigmath-thirdparty
```

如果需要经常编译，建议将`export BM_THIRDPARTY_DIR=~/tmp_work/bigmath-thirdparty`加入`~/.bashrc`或`~/.profile`文件末尾

编译代码

```shell
$ cd ~/code/bigmath-db
$ ./bm_build.sh release
```

第一次执行会从网上下载一些依赖包，如果网络不好，多运行几次`./bm_build.sh release`

如果只编译c++代码，可以加上参数`--sj`

编译完成后的程序位于`~/code/bigmath-db/build/release-clang15-dynamic-ninja/bin`目录下面，共享库们于`~/code/bigmath-db/build/release-clang15-dynamic-ninja/lib`目录下

## 四、单元测试

运行C++单元测试

```shell
$ cd ~/code/bigmath-db
$ ./bm_build.sh release --ctest
```

运行失败的用例，可以用下面语句再次运行

```shell
$ ./bm_build.sh release --ctest-args --rerun-failed
```

运行单个用例

```shell
$ ./bm_build.sh release --cxx-test testsuite_name
```

运行用例里的单个测试：<mark>#要补充</mark>

```shell
$ ./bm_build.sh release 
```

<mark>#运行Java单元测试，需要补充</mark>

参考文档：

https://docs.yugabyte.com/preview/contribute/core-database/build-from-src-ubuntu/
https://docs.yugabyte.com/preview/deploy/manual-deployment/system-config/
