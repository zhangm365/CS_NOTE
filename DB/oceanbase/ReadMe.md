
# 1. 依赖库

当出现以下错误时：
clang: error while loading shared libraries: libtinfo.so.5: cannot open shared object file: No such file or directory

安装依赖库：
`sudo apt install libncurses5`

```bash
sudo apt-get install -y libapr1


/home/bigmath/code/oceanbase/deps/3rd/usr/local/oceanbase/deps/devel/lib

sudo ln -sf /usr/lib/x86_64-linux-gnu/libapr-1.so.0.7.0 deps/3rd/usr/local/oceanbase/deps/devel/lib/libapr-1.so

sudo ln -sf /usr/lib/x86_64-linux-gnu/libapr-1.so.0.7.0 deps/3rd/usr/local/oceanbase/deps/devel/lib/libapr-1.so.0
```
