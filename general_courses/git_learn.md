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

