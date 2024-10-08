#!/bin/bash

py_file="${1:-file.py}"
json_file="${c_file%".py"}.json"

./Bash/build-dune-py.sh

./ParserPy/ptipython2json.exe "$py_file"

python3 ./MicroPyPy/main.py $json_file