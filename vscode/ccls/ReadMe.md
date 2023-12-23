
# `ccls`

[`ccls`](https://github.com/MaskRay/ccls) is a C/C++/Objective-C language server.

## 1. Build

ubuntu 系统如何编译？

```bash

git clone --depth=1 --recursive https://github.com/MaskRay/ccls
cd ccls

# Download "Pre-Built Binaries" from https://releases.llvm.org/download.html
# and unpack to /path/to/clang+llvm-xxx.
# Do not unpack to a temporary directory, as the clang resource directory is hard-coded
# into ccls at compile time!
# See https://github.com/MaskRay/ccls/wiki/FAQ#verify-the-clang-resource-directory-is-correct
cmake -H. -BRelease -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/path/to/clang+llvm-xxx

# 例如下载预构建二进制包：clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04.tar.xz
# tar 解压
# DCMAKE_INSTALL_PREFIX 指定 ccls 安装路径，例如 /usr/local
cmake -H. -BRelease -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=~/clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04 -DCMAKE_INSTALL_PREFIX=/usr/local

sudo cmake --build Release --target install


which ccls
/usr/local/bin/ccls

```
