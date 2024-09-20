# Interpreter

## How to compile

- Write `cd Interpreter/build`
- Write `cmake ..`
- Write `make`
- Write `./main`

## File organization

- token.cpp : define differents tokens
- json_reader.cpp : read json file and output the token tree
- interpreter.cpp : take the token tree and evaluate it
- main.cpp : call the different function