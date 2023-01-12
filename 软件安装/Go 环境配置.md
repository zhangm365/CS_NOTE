# Go 环境配置

本文主要针对 mac 电脑搭建 Go 语言环境

## 1. 安装 Go 

Go 官方教程
https://go.dev/doc/install



`Homebrew` 安装步骤

```Bash

$ brew install go

# 查看 Go 版本
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

```


### 2.1 vscode

1. 在命令行输入 `code .` 出现以下错误：

`zsh: command not found: code`

这个错误表示 "code ." is not working in on the command line for Visual Studio Code on OS X/Mac。

解决办法：

在 vscode 中输入 `⌘⇧P` and type `shell command` to find the Shell Command:
如下操作，然后 "Install 'code' command in PATH" 


![Image](https://github.com/zhangm365/CS_NOTE/raw/main/%E8%BD%AF%E4%BB%B6%E5%AE%89%E8%A3%85/pics/vscode.png)



1. 使用 go 命令，如 `go get ···` 等出现以下错误：

"go: go.mod file not found in current directory or any parent directory; see 'go help modules'"


```Bash
go env -w GO111MODULE=off

```









