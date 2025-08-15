
# python 环境配置

## 1. ubuntu 22.04

ubuntn 22.04 默认安装 python3 版本。

1. 安装 python3 环境

```shell
# 查看 python 配置
ls -ailh /usr/bin/python*
type python python2 python3

# link python3---> /usr/bin/python
sudo apt install python-is-python3
# install pip
sudo apt install -y python3-pip
# 在安装 pip 后，可以用如下命令安装 python package
pip3 install python_package_name
# other Dependencies
sudo apt install build-essential libssl-dev libffi-dev python3-dev
# env
sudo apt install -y python3-venv

# add ppa
sudo add-apt-repository ppa:deadsnakes/ppa
```

2. 配置系统中的 python 版本

使用 update-alternatives 命令管理多个 python 版本，并安装在 /usr/local/bin 而非 /usr/bin 目录。

```bash
# 文件 .bashrc 末尾添加 ensure the /usr/local/bin is before /usr/bin in PATH.
export PATH=/usr/local/bin:$PATH

# install python2 && python3
sudo update-alternatives --install /usr/local/bin/python python /usr/bin/python2 1
sudo update-alternatives --install /usr/local/bin/python python /usr/bin/python3 2

## 卸载
sudo update-alternatives --remove python /usr/bin/python3
# 查看关于 python 的环境配置
sudo update-alternatives --list python
# 比 list 参数更详细的 output
update-alternatives --query python
# 配置
sudo update-alternatives --config python

update-alternatives --auto python
```
