# `redis`过期键删除策略

`redis`服务器在对过期键执行删除操作时，使用的是 **惰性删除** 和 **定期删除** 两种策略，这样服务器可以很好地合理利用`CPU`和内存空间资源。

# 1. 惰性删除

过期键的惰性删除策略由`db.c/expireIfNeeded`函数实现，所有的读写数据库的`redis`命令在执行之前都会调用`expireIfNeeded`函数进行对输入键的检查：

1. 如果输入键已经过期，那么`expireIfNeeded`函数就将输入键从数据库中删除；
2. 如果没有过期，则`expireIfNeeded`不做任何操作。

以下是`expireIfNeeded`函数的源码实现：

```c
int expireIfNeeded(redisDb *db, robj *key) {
    if (!keyIsExpired(db,key)) return 0;    // 判断输入键是否过期

    /* If we are running in the context of a slave, instead of
     * evicting the expired key from the database, we return ASAP:
     * the slave key expiration is controlled by the master that will
     * send us synthesized DEL operations for expired keys.
     *
     * Still we try to return the right information to the caller,
     * that is, 0 if we think the key should be still valid, 1 if
     * we think the key is expired at this time. */
    if (server.masterhost != NULL) return 1;

    /* Delete the key */
    server.stat_expiredkeys++;
    propagateExpire(db,key,server.lazyfree_lazy_expire);
    notifyKeyspaceEvent(NOTIFY_EXPIRED,
        "expired",key,db->id);
    return server.lazyfree_lazy_expire ? dbAsyncDelete(db,key) :
                                         dbSyncDelete(db,key);
}
```

# 2. 定期删除

过期键的定期删除策略在`server.c/activeExpireCycle`函数实现，每当`redis`服务器周期性操作`server.c/serverCron`函数执行时，`activeExpireCycle`函数就会被调用，它在规定的时间内，分批次遍历服务器中的各个数据库，从数据库中的过期字典中随机检查一部分键的过期时间，并删除其中的过期键。

