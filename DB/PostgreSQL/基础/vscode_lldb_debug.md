# vscode 配置 `lldb` 调试

## 1. `lldb` 配置文件

```json
{
    // 使用 IntelliSense 了解相关属性。 
    // 悬停以查看现有属性的描述。
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "type": "lldb",
            "request": "attach",
            "name": "Attach To Process",
            "program": "${workspaceFolder}/build/release-clang15-dynamic-ninja/postgres/bin/postgres",
            "pid":"${command:pickProcess}",    
        },
        {
            "type": "lldb",
            "request": "launch",
            "name": "Launch Master",
            "program": "${workspaceFolder}/build/latest/bin/bm-master",
            "args": ["--flagfile","${workspaceFolder}/build/latest/bin/master.conf"],
            "cwd": "${workspaceFolder}"
        },
        {
            "type": "lldb",
            "request": "launch",
            "name": "Launch TServer",
            "program": "${workspaceFolder}/build/latest/bin/bm-tserver",
            "args": ["--flagfile","${workspaceFolder}/build/latest/bin/tserver.conf"],
            "cwd": "${workspaceFolder}"
        }

    ]
}
```

## 2. 错误

当遇到 `Operation not permitted` 错误提示时，需要执行以下命令：

```bash
sudo echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope

sysctl kernel.yama.ptrace_scope
kernel.yama.ptrace_scope = 0
```

- kernel.yama.ptrace_scope = 0: all processes can be debugged, as long as they have same uid. This is the classical way of how ptracing worked.
- kernel.yama.ptrace_scope = 1: only a parent process can be debugged.
- kernel.yama.ptrace_scope = 2: Only admin can use ptrace, as it required CAP_SYS_PTRACE capability.
- kernel.yama.ptrace_scope = 3: No processes may be traced with ptrace. Once set, a reboot is needed to enable ptracing again.
