#!/bin/bash

_cfilename="${1:-file.c}"
cd ParserLexer
eval $(opam env)
dune build
cd ..
cp ParserLexer/expr2json.exe .
./expr2json.exe "$_cfilename"
python3 PythonInterpreter/interpreter.py ${_cfilename%".c"}.json
