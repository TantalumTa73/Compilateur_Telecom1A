#!/bin/bash

_cfilename="${1:-file.c}"
_jsonfilename="${_cfilename%".c"}.json"
dune build --root ParserLexer >> log.txt
./ParserLexer/expr2json.exe "$_cfilename"  >> log.txt
cmake Interpreter -B Interpreter/build  >> log.txt
make -C Interpreter/build/  >> log.txt
echo "c file    : $_cfilename"  >> log.txt
echo "json file : $_jsonfilename"  >> log.txt
./Interpreter/build/main $_jsonfilename