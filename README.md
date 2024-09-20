# Imperative Compiler



## How to use Git

- [ ] [Create](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#create-a-file) or [upload](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#upload-a-file) files
- [ ] [Add files using the command line](https://docs.gitlab.com/ee/gitlab-basics/add-file.html#add-a-file-using-the-command-line) or push an existing Git repository with the following command:

```
cd existing_repo
git remote add origin https://gitlab.telecom-paris.fr/ece_3tc08_tp/imperative_compiler.git
git branch -M main
git push -uf origin main
```

## How to compile

### Dune

- Write `dune build --root ParserLexer`
- Write `./ParserLexer/expr2json.exe TestFiles/test.c`

### CMake and Make

- Write `cmake Interpreter -B Interpreter/build`
- Write `make -C Interpreter/build `
- Write `./Interpreter/main TestFiles/test.json`

