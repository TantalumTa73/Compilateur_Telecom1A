#!/bin/bash

py_file="${1:-file.py}"
json_file="${c_file%".py"}.json"

./Bash/build-dune-py.sh 
./Bash/build-micropy.sh

./ParserPy/ptipython2json.exe "$py_file"  >> log.txt
./MicroPyCpp/build/main $json_file $2