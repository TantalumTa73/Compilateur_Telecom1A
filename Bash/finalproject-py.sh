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
# python3 FinalProjectPy/core.py $json_file "FinalProjectPy/template.s"
python3 FinalProjectPy/core.py $json_file "PythonCompiler/template.s"
# cd ..
# gcc $s_file -o $out_file
# ./$out_file
# You just need to compute the .s file, not to run it

# The error when I try your compiler :
# python3 FinalProjectPy/core.py TestFinal/variable.json "PythonCompiler/template.s"
# {'action': 'vardef', 'type': 'int', 'name': 'a', 'size': [], 'value': {'action': 'litteral', 'value': {'action': 'int', 'value': 0}}}
# Traceback (most recent call last):
#   File "/cal/exterieurs/yruellan-24/IMP_comp/imperative_compiler/FinalProjectPy/core.py", line 576, in <module>
#     define_function(element["name"], element["type"], element["args"], scope, appened)
#   File "/cal/exterieurs/yruellan-24/IMP_comp/imperative_compiler/FinalProjectPy/core.py", line 432, in define_function
#     evaluate_scope(scope["body"], funcname, return_type, current_depth)
#   File "/cal/exterieurs/yruellan-24/IMP_comp/imperative_compiler/FinalProjectPy/core.py", line 213, in evaluate_scope
#     VARIABLE_OFFSET += memory_var_size
# TypeError: unsupported operand type(s) for +=: 'int' and 'list'