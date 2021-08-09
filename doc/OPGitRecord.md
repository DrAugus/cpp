## git如何取消merge

当我们使用git merge操作合并代码但还没add时，若想取消这次合并，使用`git merge --abort`命令即可  
![img.png](../image/OPGitRecord/img.png)

假如不幸已经 `git add` 了怎么办呢？ 其实也很简单，先用 `git reflog` 指令显示历史的操作  
![img_1.png](../image/OPGitRecord/img_1.png)

再用 `git reset --hard commit id`就可以回退到操作之前的状态了

## linux下git免密码登录配置

1. 编辑`git-credentials`文件(如果没有 键入 `touch .git-credentials`)
    * `vi .git-credentials`

2. 文件中添加`https://username:passeord@项目地址`
    * 如果账号密码中有@符号，用40%代替

3. `git config --global credential.helper store`

4. `vi .gitconfig` 出现 `helper = store` 或者

```
cat .gitconfig

[credential]
helper = store 
```
