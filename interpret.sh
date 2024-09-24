#!/bin/bash

_cfilename="${1:-file.c}"
dune build --root ParserLexer >> log.txt
./ParserLexer/expr2json.exe "$_cfilename"  >> log.txt
cmake Interpreter -B Interpreter/build  >> log.txt
make -C Interpreter/build/  >> log.txt
y="${_cfilename%".c"}.json"
echo "y is $y"
./Interpreter/build/main $y