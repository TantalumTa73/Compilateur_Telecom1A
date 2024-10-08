#!/bin/bash

_cfilename="${1:-file.c}"

./Bash/build-dune.sh
./Bash/parse $_cfilename

python3 PythonCompiler/compiler.py ${_cfilename%".c"}.json PythonCompiler/template.s
