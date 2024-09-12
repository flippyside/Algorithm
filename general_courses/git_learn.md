- 新建一个远程仓库
- 推送大文件后..

# 新建一个远程仓库

```
// 首先创建一个本地仓库
git init

// 生成新的 SSH 密钥
ssh-keygen -t ed25519 -C "your_new_email@example.com" -f ~/.ssh/id_ed25519_newrepo

// 将新的 SSH 私钥添加到 SSH 代理中
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519_newrepo

// 复制新的 SSH 公钥并将其添加到 GitHub
cat ~/.ssh/id_ed25519_newrepo.pub 

// 配置 SSH 配置文件
编辑 ~/.ssh/config 文件: 
Host github.com-newrepo
  HostName github.com
  User git
  IdentityFile ~/.ssh/id_ed25519_newrepo  # 或 `~/.ssh/id_rsa_newrepo`

Host github.com
  HostName github.com
  User git
  IdentityFile ~/.ssh/id_ed25519  # 或 `~/.ssh/id_rsa`

克隆或更新远程仓库 URL
git clone git@github.com-newrepo:username/new-repo.git
或者 git remote set-url origin git@github.com-newrepo:username/new-repo.git
```

# 推送大文件后..

1. 首先，使用以下命令删除要移除的文件：
git rm 文件路径
将 “文件路径” 替换为要删除的文件的实际路径。这将从 Git 仓库中删除该文件，并将其放入暂存区。git rm 相当于 linux rm + git add 命令。

2. 使用以下命令修改上一次的提交：
git commit --amend -m '提交描述'
之前的提交记录会被新的提交覆盖

3. 最后，使用以下命令将修改后的提交推送到远程仓库：
git push --force

push大文件(超过100M)后，删除大文件后commit, 

remote: warning: File Japanese/大家的日语 初级1 第二版 学习辅导用书.pdf is 86.84 MB; this is larger than GitHub's recommended maximum file size of 50.00 MB
remote: error: Trace: d3bfc893383b585992e68b44c2afe106fa0860c6e6056c6d7af3a6566241157e
remote: error: See https://gh.io/lfs for more information.
remote: error: File Japanese/大家的日语 初级1 第二版.pdf is 163.55 MB; this exceeds GitHub's file size limit of 100.00 MB
remote: error: File 数据结构、算法与应用（原书第2版） C++语言描述 (Sartaj Sahni) (Z-Library).pdf is 215.81 MB; this exceeds GitHub's file size limit of 100.00 MB
remote: error: GH001: Large files detected. You may want to try Git Large File Storage - https://git-lfs.github.com.
To github.com:flippyside/Algorithm.git
 ! [remote rejected] master -> master (pre-receive hook declined)
error: failed to push some refs to 'github.com:flippyside/Algorithm.git'

