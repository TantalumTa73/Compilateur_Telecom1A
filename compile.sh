#!/bin/bash

_cfilename="${1:-file.c}"
cd ParserLexer
eval $(opam env)
dune build
cd ..
cp ParserLexer/expr2json.exe .
./expr2json.exe "$_cfilename"
python3 PythonCompiler/compiler.py ${_cfilename%".c"}.json PythonCompiler/template.s
