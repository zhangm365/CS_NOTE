
# `gdb` 如何读取 `core dumped` 文件

## 1. 配置生成 `core dumped` 文件

```bash

# gdb core dumped file
ulimit -c
# 可以写入 /etc/profile 或者 ~/.bashrc，使得每次登录都生效
ulimit -c unlimited


# 文件命名格式：%e：可执行文件名，%p：dumped进程的PID，%s：导致dump的信号个数，
# %t：dump的时间，精确到秒，%c：core file大小的限制
sudo echo "core-%e-%p-%s-%t-%c" > /proc/sys/kernel/core_pattern

# 控制 core 文件是否包含 PID
sudo echo "1" > /proc/sys/kernel/core_uses_pid
```

## 2. 读取 `core dumped` 文件

```bash
gdb 程序名 corefile
```
