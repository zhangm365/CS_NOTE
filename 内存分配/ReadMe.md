
# 内存分配机制

主要包括 tcmalloc, jemalloc, glibc malloc 等

## 1. TCMalloc

[TCMalloc](https://github.com/google/tcmalloc) 是谷歌内部的内存分配项目，它从 `Google Perftools` 中分离出来，是一款开源高效的线程安全内存分配器，之后被社区称为 `gperftools`。
