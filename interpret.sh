#!/bin/bash

dune build --root ParserLexer
./ParserLexer/expr2json.exe TestFiles/file.c
cmake Interpreter -B Interpreter/build
make -C Interpreter/build/
./Interpreter/build/main TestFiles/file.json