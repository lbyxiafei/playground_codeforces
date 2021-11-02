
## Git ignore
- Add .gitignore to repo
    - ```git rm -rf --cached .```
    - ```git add .```
- Weak ignore: [ignored but not deleted by ```git clean```](https://stackoverflow.com/questions/6317169/using-gitignore-to-ignore-but-not-delete-files/16442091)
  - ```git update-index --assume-unchanged <file>```
  - Revert: ```git update-index --no-assume-unchanged <file>```
  - Check ignore status: ```git ls-files -v | grep '^h'```
    - H means normal committed file
    - h stands for **weak ignored**
