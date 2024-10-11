#!/bin/bash

py_file="${1:-file.py}"
json_file="${py_file%".py"}.json"

echo "Compiling $py_file to $json_file"

./Bash/build-dune-py.sh 
./Bash/build-micropy.sh

# ./ParserPy/ptipython2json.exe "$py_file"  >> log.txt
./MicroPyCpp/build/main $json_file $2