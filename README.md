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

- Parser : Delete Parentesis token
- Parser : fusion expr and term ?
- Interpreter : Unify local / global variable system
- New feature : Define and set variable `int x = 1`
- New feature : Ignore `#define <stdio.h>`
- New feature : Support `x = +1`
- New feature : operation `cond ? x : y `
- New feature : operatior of assignment, Comparison, Logical, Bitwise