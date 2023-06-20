
# vscode 配置 lldb 调试

## 1. lldb 配置文件

```bash
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

当遇到 Operation not permitted 错误提示时，需要执行以下命令：

```bash
sudo echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
```
