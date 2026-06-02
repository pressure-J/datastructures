# Git 与 GitHub 基本操作指南

## 一、Git 基础配置

### 1.1 设置用户信息
```bash
git config --global user.name "你的用户名"
git config --global user.email "你的邮箱@example.com"
```

### 1.2 查看配置信息
```bash
git config --list
```

---

## 二、本地仓库操作

### 2.1 初始化仓库
```bash
# 在项目目录下初始化 Git 仓库
git init
```

### 2.2 查看状态
```bash
# 查看当前工作区状态
git status

# 简洁模式
git status -s
```

### 2.3 添加文件到暂存区
```bash
# 添加指定文件
git add 文件名

# 添加所有文件
git add .

# 添加所有修改和删除（不包括新文件）
git add -u
```

### 2.4 提交更改
```bash
# 提交并添加说明
git commit -m "提交说明"

# 添加并提交所有已跟踪文件
git commit -am "提交说明"
```

### 2.5 查看提交历史
```bash
# 简洁模式
git log --oneline

# 图形模式显示分支
git log --oneline --graph --all

# 查看最近 n 次提交
git log -n 5
```

### 2.6 查看差异
```bash
# 工作区与暂存区的差异
git diff

# 暂存区与最新提交的差异
git diff --staged

# 查看某次提交的改动
git show 提交ID
```

### 2.7 撤销操作
```bash
# 撤销工作区修改（未 add）
git checkout -- 文件名

# 撤销暂存区修改（已 add 未 commit）
git reset HEAD 文件名

# 撤销最近一次提交（保留修改）
git reset --soft HEAD~1

# 撤销最近一次提交（丢弃修改，慎用！）
git reset --hard HEAD~1
```

---

## 三、分支管理

### 3.1 分支基本操作
```bash
# 查看本地分支
git branch

# 查看所有分支（包括远程）
git branch -a

# 创建新分支
git branch 分支名

# 切换分支
git checkout 分支名

# 创建并切换到新分支
git checkout -b 分支名

# 删除分支
git branch -d 分支名

# 强制删除分支
git branch -D 分支名
```

### 3.2 合并分支
```bash
# 切换到目标分支
git checkout main

# 合并指定分支
git merge 分支名

# 合并后删除分支
git merge --no-ff 分支名
```

### 3.3 解决冲突
当合并出现冲突时：
1. 打开冲突文件，找到 `<<<<<<<`、`=======`、`>>>>>>>` 标记
2. 手动修改冲突内容
3. `git add` 标记为已解决
4. `git commit` 完成合并

---

## 四、远程仓库操作（GitHub）

### 4.1 关联远程仓库
```bash
# 添加远程仓库
git remote add origin https://github.com/用户名/仓库名.git

# 查看远程仓库
git remote -v

# 修改远程仓库地址
git remote set-url origin https://github.com/用户名/仓库名.git

# 删除远程仓库
git remote remove origin
```

### 4.2 推送到远程
```bash
# 首次推送并关联分支
git push -u origin main

# 后续推送
git push

# 推送指定分支
git push origin 分支名

# 强制推送（慎用！）
git push -f origin main
```

### 4.3 拉取远程更新
```bash
# 拉取并合并
git pull

# 拉取指定分支
git pull origin 分支名

# 仅获取远程更新（不合并）
git fetch origin
```

### 4.4 克隆仓库
```bash
# 克隆远程仓库
git clone https://github.com/用户名/仓库名.git

# 克隆到指定目录
git clone https://github.com/用户名/仓库名.git 目录名
```

---

## 五、团队协作工作流

### 5.1 Fork + Pull Request 模式
1. **Fork** 项目到自己的 GitHub
2. **Clone** 到本地
3. 创建新分支进行开发
4. 推送到自己的远程仓库
5. 在 GitHub 上发起 **Pull Request**
6. 等待项目维护者审核合并

### 5.2 日常协作流程
```bash
# 1. 开始工作前，先拉取最新代码
git pull origin main

# 2. 创建功能分支
git checkout -b feature-功能名

# 3. 开发并提交
git add .
git commit -m "完成XX功能"

# 4. 推送到远程
git push origin feature-功能名

# 5. 在 GitHub 发起 Pull Request

# 6. 合并后删除本地分支
git checkout main
git pull
git branch -d feature-功能名
```

---

## 六、常用技巧

### 6.1 .gitignore 文件
创建 `.gitignore` 文件来忽略不需要版本控制的文件：
```
# 编译产物
*.o
*.exe
*.class

# IDE 文件
.vscode/
.idea/
*.swp

# 依赖目录
node_modules/
vendor/

# 系统文件
.DS_Store
Thumbs.db
```

### 6.2 查看帮助
```bash
# 查看 git 命令帮助
git help 命令名

# 例如
git help commit
git help push
```

### 6.3 设置命令别名
```bash
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
```

---

## 七、常见问题处理

### 7.1 推送被拒绝
```bash
# 先拉取远程更新
git pull origin main --rebase

# 解决冲突后推送
git push origin main
```

### 7.2 误删文件恢复
```bash
# 从最新提交恢复文件
git checkout HEAD 文件名
```

### 7.3 查看某个文件的修改历史
```bash
git log -p 文件名
```

---

*最后更新：2026年*
