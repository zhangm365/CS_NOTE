
# `git stash drop` 恢复

```bash
# 查找 hash_id，保存到 find.txt
git fsck --unreachable | awk '{print $3}' | xargs git show > find.txt

# 或者在命令行输出
git log --graph --decorate --pretty=oneline --abbrev-commit --all $(git fsck --no-reflogs | grep commit | cut -d' ' -f3)

# 根据 hash_id 恢复
git stash apply &stash_hash_id
```
