#!/bin/bash

c_file="${1:-file.c}"
json_file="${c_file%".c"}.json"

./Bash/build-dune-py.sh

./ParserPy/expr2json.exe "$c_file"

python3 ./MicroPyPy/main.py $json_file