
# 查找/usr/include/ 目录下包含字符串为sockaddr_in的文件
```shell

find /usr/include/ | xargs grep "sockaddr_in"
find /usr/include/ | xargs grep -ri "string"


```

