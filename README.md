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

## How to use


### Build a sub-project
To build a sub project, write :
- `./Bash/build-dune.sh`
- `./Bash/build-compiler.sh`
- `./Bash/build-interpret.sh`

### Run on file
To run a file, write :
- `./Bash/parse.sh my_file`
- `./Bash/compile-cpp.sh my_file`
- `./Bash/interpret-cpp.sh my_file`

### Test on examples :
To view which test pass or not, write :
- `./Bash/test-parser.sh`
- `./Bash/test-interpret.sh`


## TODO list

- Delete Parentesis token is parser
- Add operation `cond ? x : y ;`
- Unify local / global variable in interpreter.cpp
- Define and set variable `int x = 1;`
- Support `#define <stdio.h>`