#!/bin/bash

c_file="${1:-file.c}"
json_file="${c_file%".c"}.json"
s_file="${c_file%".c"}.s"

echo ""  >> log.txt
echo "------------------------------------"  >> log.txt
echo "c file    : $c_file"  >> log.txt
echo "json file : $json_file"  >> log.txt

set -e

./Bash/build-dune-finalproject.sh || (echo "Failed to build dune"; exit 1;)
./Bash/build-finalproject-cpp.sh || (echo "Failed to build finalproject-cpp"; exit 1;)

touch "$s_file" || (echo "Failed to create file"; exit 1;)
touch "file.s" || (echo "Failed to create sample s file"; exit 1;)

cat FinalProjectCpp/template.s > "file.s"
echo "main:" >> "file.s"
echo "    mov %rbp, %rsp" >> "file.s"
echo "    pop %rbp" >> "file.s"
echo "    ret" >> "file.s"
echo "    .section .note.GNU-stack" >> "file.s"

./ParserBetter/expr2json.exe "$c_file"  >> log.txt || (echo "Failed to run expr2json"; exit 1;)
./FinalProjectCpp/build/main $json_file $2 || (echo "Failed to run finalproject-cpp"; exit 1;)