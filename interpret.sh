#!/bin/bash

_cfilename="${1:-file.c}"
dune build --root ParserLexer
./ParserLexer/expr2json.exe "$_cfilename"
cmake Interpreter -B Interpreter/build
make -C Interpreter/build/
./Interpreter/build/main "${_cfilename%".c"}.json"