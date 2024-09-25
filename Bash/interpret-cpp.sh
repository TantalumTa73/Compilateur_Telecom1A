#!/bin/bash

_cfilename="${1:-file.c}"
_jsonfilename="${_cfilename%".c"}.json"

echo ""  >> log.txt
echo "------------------------------------"  >> log.txt
echo "c file    : $_cfilename"  >> log.txt
echo "json file : $_jsonfilename"  >> log.txt

./Bash/build-dune.sh
./Bash/build-interpret.sh


./ParserLexer/expr2json.exe "$_cfilename"  >> log.txt
./Interpreter/build/main $_jsonfilename