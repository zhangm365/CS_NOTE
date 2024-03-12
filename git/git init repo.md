# git init repo

`git` 创建仓库的几种方法。

## 1. 全局配置

```bash
# Git global setup
git config --global user.name "username"
git config --global user.email "xxx@email.com"
```

## 2. 创建新仓库

初始化仓库。

```bash
# 1. Create a new repository
git clone ssh://git@src-url.git
cd apache-seatunnel-web-1.0.0-src
git switch --create main
touch README.md
git add README.md
git commit -m "add README"
git push --set-upstream origin main

# 2. Push an existing folder
cd existing_folder
git init --initial-branch=main
git remote add origin ssh://git@src-url.git
git add .
git commit -m "Initial commit"
git push --set-upstream origin main


# 3. Push an existing Git repository
cd existing_repo
git remote rename origin old-origin
git remote add origin ssh://git@192.168.50.187:9922/zhangmao/apache-seatunnel-web-1.0.0-src.git
git push --set-upstream origin --all
git push --set-upstream origin --tags
```
