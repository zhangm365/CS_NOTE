# Go 环境配置

本文主要针对 mac 电脑搭建 Go 语言环境

## 1. 安装 Go 

Go 官方教程
https://go.dev/doc/install



`Homebrew` 安装步骤

```Bash
# 首先要成功安装 Homebrew 工具，可以从清华镜像网站安装。
# https://mirrors.tuna.tsinghua.edu.cn/help/homebrew/

$ brew install go

# 安装成功后，查看 Go 版本
$ go version
go version go1.19.5 darwin/arm64

```


## 2. Go 环境

Go 有一套特殊的惯例。

按照惯例，所有 Go 代码都存在于一个工作区（文件夹）中。这个工作区可以在你的机器的任何地方。如果你不指定，Go 将假定 $HOME/go 为默认工作区。工作区由环境变量 GOPATH 标识并修改。

在 .bash_profile 中添加以下语句：

```Bash

export GOPATH=$HOME/go
export PATH=$PATH:$GOPATH/bin

# Go 把文件放到三个目录：源码位于 .../src，包对象位于 .../pkg，编译好的程序位于 .../bin 目录下。
mkdir -p $GOPATH/src $GOPATH/pkg $GOPATH/bin

```


### 2.1 vscode

本文使用 vscode 编辑器作为学习 Go 语言的工具，以下是在 vscode 中配置 Go 插件的配置步骤。

1. 在命令行输入 `code .` 出现以下错误：

`zsh: command not found: code`

这个错误表示 "code ." is not working in on the command line for Visual Studio Code on OS X/Mac。

解决办法：

在 vscode 中输入 `⌘⇧P` and type `shell command` to find the Shell Command:
如下操作，然后 "Install 'code' command in PATH" 


![Image](https://github.com/zhangm365/CS_NOTE/raw/main/%E8%BD%AF%E4%BB%B6%E5%AE%89%E8%A3%85/pics/vscode.png)



2. 使用 go 命令，如 `go get ···` 等出现以下错误：

"go: go.mod file not found in current directory or any parent directory; see 'go help modules'"


```Bash
go env -w GO111MODULE=off

```

3. 解决 vscode 安装 Go Tools 失败问题

在 vscode 中安装官方的 Go 插件后，然后软件会提示安装 Go Tools，但总会失败。

```bash
Installing github.com/cweill/gotests/... FAILED
Installing github.com/fatih/gomodifytags FAILED
Installing github.com/josharian/impl FAILED
```

解决方案：

```bash

$ go env -w GO111MODULE=on
$ go env -w GOPROXY=https://goproxy.io,direct

```

References:
- https://goproxy.io/zh/
- https://github.com/microsoft/vscode-go/issues/3129





