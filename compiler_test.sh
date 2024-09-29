#!/bin/bash

_cfilename="${1:-file.c}"
dune build --root ParserLexer
./ParserLexer/expr2json.exe "$_cfilename"
cmake Compiler -B Compiler/build
make -C Compiler/build/
./Compiler/build/main "${_cfilename%".c"}"
