
# `AddressSanitizer`

[`AddressSanitizer`](https://clang.llvm.org/docs/AddressSanitizer.html#introduction) 是一个快速内存检测工具，并成为 `LLVM(v3.1)` 和 `GCC(v4.8)` 编译工具链的一部分，它包括编译时插桩模块和运行库。

`ASan` 通过在编译时插入检测代码和程序运行时可以检测以下错误：

1. Out-of-bounds accesses to Heap, Stack and Globals
2. Use-after-free
3. Use-after-return
4. Use-after-scope
5. Double-free, invalid free
6. Memory leaks
