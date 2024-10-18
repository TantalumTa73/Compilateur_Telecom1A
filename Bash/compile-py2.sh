#!/bin/bash

c_file="${1:-file.c}"
json_file="${c_file%".c"}.json"
x86_file="${c_file%".c"}.s"

echo "Compiling $c_file to $x86_file (json: $json_file)"

./Bash/build-dune.sh
./ParserLexer/expr2json.exe $c_file

python3 PythonCompiler/compiler.py $json_file "PythonCompiler/template.s"
