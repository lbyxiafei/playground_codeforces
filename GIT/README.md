
## Git ignore
- Add .gitignore to repo
    - ```git rm -rf --cached .```
    - ```git add .```
### Weak ignore
- Weak ignore: [ignored but not deleted by ```git clean```](https://stackoverflow.com/questions/6317169/using-gitignore-to-ignore-but-not-delete-files/16442091)
  - ```git update-index --assume-unchanged <file>```
  - Revert: ```git update-index --no-assume-unchanged <file>```
  - Check ignore status: ```git ls-files -v | grep '^h'```
    - H means normal committed file
    - h stands for **weak ignored**
## Commit revise
- 修改历史commit的内容（一时疏忽泄露的敏感信息）
    - `git rebase --interactive 'bbc643cd^'`
        - git bash会在vim编辑器中显示一些rebase的信息, 我将bbc643cd对应的那一行的pick改成edit后保存 (:wq)
        - 然后在本地文件上删除掉那些敏感信息, 运行如下命令提交修改
    - `git commit --all --amend --no-edit` 
    - `git rebase --continue`
    - `git push --force`