#!/bin/bash

c_file="${1:-file.c}"
s_file="${c_file%".c"}.s"
out_file="${c_file%".c"}.out"
json_file="${c_file%".c"}.json"

eval $(opam env)

echo ""  >> log.txt
echo "------------------------------------"  >> log.txt
echo "c file    : $c_file"  >> log.txt
echo "json file : $json_file"  >> log.txt


./Bash/build-dune-finalproject.sh > /dev/null 2>&1


./ParserBetter/expr2json.exe "$c_file"  >> log.txt
python3 FinalProjectPy/core.py $json_file "FinalProjectPy/template.s"
# cd ..
gcc $s_file -o $out_file
./$out_file
