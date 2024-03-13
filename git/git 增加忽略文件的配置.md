
# git 增加忽略文件的配置

基本配置是在当前目录增加 `.gitignore` 文件，然后在文件中增加需要忽略的文件或目录。

```bash

# how to make Git forget about a file that was tracked, but is now in .gitignore?
git rm -r --cached . && git add . && git commit -am "Remove ignored files"
git push

# git filter-repo --path <filename | dir_name> --invert-paths

# 当删除已跟踪的文件或目录时，如下是删除仓库的所有 target 目录。
# git filter-repo --path target --invert-paths

# # 清理 git 垃圾
# git reflog expire --expire=now --all
# git gc --prune=now --aggressive
```
