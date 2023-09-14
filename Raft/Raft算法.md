
# [`Raft` 算法](https://raft.github.io/)

在分布式系统中，为了提高系统集群的容错性，分布式集群中需要包括多个节点。
那么如何保证集群各个节点数据的一致性？

`Raft` 是一种保证数据一致性的共识算法。每个节点（服务器）包括**状态机和日志**，状态机用于存储数据，日志用于记录状态机的更改记录。`Raft` 算法的核心就是保证各个节点的日志一致，从而使得各个节点状态机中的数据一致。

## 1. 角色

在 `Raft` 中，节点的有三种角色：

1. `Leader`：处理客户端请求，将 `Raft Log` 复制到其他节点，当大多数节点确认后，将日志应用到状态机；
2. `Follower`：处理来自 `Leader` 和 `Candidate` 的请求，如果在超时时间内没有收到 `Leader` 的心跳，将转换为 `Candidate`；
3. `Candidate`：向其他节点发起投票请求，等待其他大多数节点投票同意后成为 `Leader`。

每个节点的初始状态是 `Follower` 角色。

## 2. 选举流程

`Raft` 中包括两个 `timeout`(超时时间) 来控制选举过程，
这个时间的随机初始化区间：[150ms, 300ms]。

1. `election timeout`：`Follower` 转换为 `Candidate` 的超时时间；
    一个 `Leader` 选举过程如下：

    a. 当 `Follower` 从时间 `election timeout` 开始倒计时为 0 后，转为 `Candidate` 角色，并向其他对端节点发起投票请求；

    b. 如果 `Follower` 在这个选举周期内没有收到其他节点的投票请求，那么就会投票给当前的 `Candidate`，并重置 `election timeout`；

    c. 一旦 `Candidate` 收到其他大多数对端节点的投票请求同意后，它将转为 `Leader` 角色，然后向其他节点发送 `heartbeat timeout`，表示本次选举成功。

2. `heartbeat timeout`：`Leader` 发送心跳的超时时间。

    主要是用于保持各个节点之间的心跳响应，防止 `Leader` 节点宕机而停止服务。

## 3. `Log Replication`

在分布式系统中，客户端所有的请求都是发送给 `Leader` 节点，然后由 `Leader` 节点将 `Raft Log` 复制到其他节点，当大多数节点确认后，`Leader` 节点再向客户端返回请求结果。

`Raft` 中的 `Raft Log` 复制流程如下：

1. `Leader` 将接收到的客户端请求追加到自己的 `Raft Log` 中，并复制给其他 `Follower` 节点；
2. `Follower` 将修改同步到自己的 `Raft Log` 中；
3. `Leader` 收到其他大多数 `Follower` 的 `Raft Log` 写完成后，然后提交本次修改到状态机，并向客户端返回结果；
4. `Leader` 再向其他 `Follower` 发送心跳信息，通知其他 `Follower` 本次修改已提交。其他节点后台提交本次修改，保证与 `Leader` 的状态机数据是一致的。
