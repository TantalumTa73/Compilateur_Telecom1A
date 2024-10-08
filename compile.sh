#!/bin/bash

# ./Bash/interpret-cpp.sh $1 $2

# ./Bash/compile-py.sh $1

_cfilename="${1:-file.c}"
cd ParserLexer
eval $(opam env)
dune build
cd ..
cp ParserLexer/expr2json.exe .
./expr2json.exe "$_cfilename"
python3 PythonCompiler/compiler.py ${_cfilename%".c"}.json PythonCompiler/template.s
