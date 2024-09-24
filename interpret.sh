#!/bin/bash

cd ParserLexer
eval $(opam env)
dune build
cd ..
cp ParserLexer/expr2json.exe .
./expr2json.exe $1.c
python3 PythonInterpreter/interpreter.py $1.json
