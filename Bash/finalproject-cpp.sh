#!/bin/bash

c_file="${1:-file.c}"
json_file="${_cfilename%".c"}.json"

echo ""  >> log.txt
echo "------------------------------------"  >> log.txt
echo "c file    : $c_file"  >> log.txt
echo "json file : $json_file"  >> log.txt


./Bash/build-dune-finalproject.sh.sh
./Bash/build-finalproject-cpp.sh


./ParserBetter/expr2json.exe "$c_file"  >> log.txt
./FinalProjectCpp/build/main $json_file $2