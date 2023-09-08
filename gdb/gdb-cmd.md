
# `GDB` 命令

## 1.常用命令

```bash
# help
gdb> help info proc
# 查看内存布局
gdb> info proc mappings
# 查看内存中的符号表
gdb> info proc symtab
# 查看内存中的函数
gdb> info proc functions
# 查看内存中的变量
gdb> info proc variables
# 查看内存中的线程
gdb> info threads
# 查看内存中的线程栈
gdb> info threads backtrace
```
