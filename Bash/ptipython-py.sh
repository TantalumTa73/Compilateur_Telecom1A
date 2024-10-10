#!/bin/bash

py_file="${1:-file.py}"
json_file="${py_file%".py"}.json"

# ./Bash/build-dune-py.sh 
./Bash/build-dune-py.sh > /dev/null 2>&1

./ParserPy/ptipython2json.exe "$py_file" >> log.txt

python3 MicroPy/micropy_interpreter.py $json_file