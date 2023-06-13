
# k8s 安装配置

## 1. `kubeadm`、`kubelet` 和 `kubectl`

`kubeadm`: 用来初始化集群指令。
`kubelet`: 在集群中的每个节点上用来启动 Pod 和容器等。
`kubectl`: 用来与集群通信的命令行工具。

1. 安装 k8s `apt` 仓库所需要的包

```bash
sudo apt-get update
sudo apt-get install -y apt-transport-https ca-certificates curl
```

2. 下载 Google Cloud 公开签名密钥

```bash
curl -fsSL https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo gpg --dearmor -o /etc/apt/keyrings/kubernetes-archive-keyring.gpg
```

但通常会遇到超时无法访问 Google Cloud 网站，因此可以手动下载 `[apt-key.gpg](https://packages.cloud.google.com/apt/doc/apt-key.gpg)` 文件，然后通过以下命令操作：

```bash
sudo gpg --dearmor -o /etc/apt/keyrings/kubernetes-archive-keyring.gpg /path/to/your/apt-key.gpg

```

3. 添加 k8s `apt` 仓库

```bash
echo "deb [signed-by=/etc/apt/keyrings/kubernetes-archive-keyring.gpg] https://apt.kubernetes.io/ kubernetes-xenial main" | sudo tee /etc/apt/sources.list.d/kubernetes.list
```

但也会遇到无法访问的问题，因此将 `https://apt.kubernetes.io/` 修改为 `https://mirrors.tuna.tsinghua.edu.cn/kubernetes/apt/`：

```bash
echo "deb [signed-by=/etc/apt/keyrings/kubernetes-archive-keyring.gpg] https://mirrors.tuna.tsinghua.edu.cn/kubernetes/apt/ kubernetes-xenial main" | sudo tee /etc/apt/sources.list.d/kubernetes.list
```

4. 安装 `kubeadm`、`kubelet` 和 `kubectl`，并锁定版本

```bash
sudo apt-get update
sudo apt-get install -y kubelet kubeadm kubectl
sudo apt-mark hold kubelet kubeadm kubectl
```
