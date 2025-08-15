
# 设置 `ssh` 公钥身份验证连接远程服务器

如果通过 `ssh` 公钥连接远程服务器？

## 1. `ssh`

`ssh` 公钥身份认证连接远程服务器是一种更安全的通信方式，它依赖于非对称加密算法，该算法产生一对密钥，一个是私钥，一个是公钥。

具体可用于客户端与服务端之间的通信场景。

## 2. 验证流程

具体流程如下：

```shell
# 1. 客户端使用 RSA 算法生成一对密钥。这个命令会在 ~/.ssh/ 目录下生成私钥和公钥：
# 私钥：~/.ssh/id_rsa
# 公钥：~/.ssh/id_rsa.pub
ssh-keygen -t rsa

# 2. 将公钥复制到远程服务端
scp ~/.ssh/id_rsa.pub username@remote-ip

# 或者将公钥复制到远程服务器，这样客户端可以免密登录服务器：
mkdir -p ~/.ssh
touch ~/.ssh/authorized_keys

cat ~/id_rsa.pub >> ~/.ssh/authorized_keys

```
