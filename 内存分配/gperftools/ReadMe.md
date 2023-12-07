
# `gperftools` 介绍

它是一个 `Google` 开源的性能分析工具，通过 `Library` 的技术原理实现。

1. 通过 `tcmalloc` 实现内存分配机制。
2. 通过 LD_PRELOAD 的方式加载，替换掉系统的 malloc 等函数，从而实现性能分析。
3. 使用 pprof 工具分析生成的报告文件。
