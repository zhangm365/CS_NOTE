
# 1. 指南

`Valgrind` 是一个动态二进制插桩（Dynamic Binary Instrumentation, DBI）框架，用于构建动态二进制分析工具（Dynamic Binary Analysis, DBA）。

这些工具是作为 `Valgrind` 的插件实现的，可以用来检测许多内存管理和线程错误问题，并对程序进行详细剖析，例如 `Memcheck` 内存检测工具。

`Valgrind` 框架支持影子值（shadow values）的概念，它是一种强有力的动态二进制分析技术，它要求工具将每个寄存器和内存值影子化为另一个元数据值，用于追踪和分析程序运行时的内存使用情况。

# 2. 原理

当 `Valgrind` 加载可执行程序运行时，通过将机器码重新编译称为 `UCode` 的中间表示形式，在 `UCode` 中插入检测代码，然后将 `UCode` 重转换为机器码执行。
