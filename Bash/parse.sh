#!/bin/bash

_cfilename="${1:-file.c}"


echo ""  >> log.txt
echo "------------------------------------"  >> log.txt
echo "c file    : $_cfilename"  >> log.txt

./Bash/build-dune.sh

./ParserLexer/expr2json.exe "$_cfilename"