#!/bin/bash

_cfilename="${1:-file.c}"
_jsonfilename="${_cfilename%".c"}.json"
_sfilename="${_cfilename%".c"}.s"
_exefilename="${_cfilename%".c"}"


echo ""  >> log.txt
echo "------------------------------------"  >> log.txt
echo "c file    : $_cfilename"  >> log.txt
echo "json file : $_jsonfilename"  >> log.txt

./Bash/build-dune.sh
./Bash/build-compiler.sh


./ParserLexer/expr2json.exe "$_cfilename"  >> log.txt
./Compiler/build/main $_jsonfilename >> log.txt