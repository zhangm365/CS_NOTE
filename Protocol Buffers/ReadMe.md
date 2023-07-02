# bazel 安装

## 1. 使用 bazelisk 安装 bazel

在 `maxOS` 上使用 `brew` 安装 `[bazelisk](https://github.com/bazelbuild/bazelisk)`

```bash
brew install bazelisk
```

如何在使用过程中遇到问题，例如以下错误：
[could not resolve the version 'latest' to an actual version num]
(https://github.com/bazelbuild/bazelisk/issues/220)

则可以在包括 `WORKSPACE` 的目录下指定 `bazel` 的版本：

```bash
# bazel LTS release 版本可以在 https://github.com/bazelbuild/bazel/releases 查看
echo "USE_BAZEL_VERSION=6.2.1" > .bazeliskrc
```

也可以在 `~/.zshrc` 中指定全局的 `bazel` 版本下载链接。

```bash
export BAZELISK_BASE_URL=https://github.com/bazelbuild/bazel/releases/download
```
