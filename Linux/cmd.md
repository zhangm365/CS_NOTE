
# `Linux` 常见命令

# 1. 将终端输出内容重定向到文件

```bash
# >&: 表示将标准输出和标出错误重定向到 file 文件，最后的 & 表示当前命令以后台的方式执行
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
