# Imperative Compiler



## How to use Git


```
cd existing_repo
git init
git remote add origin https://gitlab.telecom-paris.fr/ece_3tc08_tp/imperative_compiler.git
git branch -M main
git pull origin main
<!-- git push -uf origin main -->
```

## How to compile

### ParserLexer

#### Compile
To compile the project, write `dune build --root ParserLexer`.

#### Run on file
To run on a file, write `./ParserLexer/expr2json.exe TestFiles/my_file.c`

#### Test on examples :
To view which test pass or not, write :
- `cmake TestFiles -B TestFiles/build`
- `cmake --build TestFiles/build`
- `ctest --test-dir TestFiles/build`

When you modify something in ParserLexer, please add a test file in TestFiles.

### Interpreter

- Write `cmake Interpreter -B Interpreter/build`
- Write `make -C Interpreter/build `
- Write `./Interpreter/build/main TestFiles/my_file.json`

