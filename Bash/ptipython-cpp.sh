#!/bin/bash

c_file="${1:-file.c}"
json_file="${c_file%".c"}.json"

./Bash/build-dune-py.sh 
./Bash/build-micropy.sh

./ParserPy/expr2json.exe "$c_file"  >> log.txt
./MicroPyCpp/build/main $json_file $2