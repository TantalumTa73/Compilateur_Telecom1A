#!/bin/bash

# touch "_temp.c"
# echo "#include <stdlib.h>" > "_temp.c"
# echo "#include <stdio.h>" >> "_temp.c"
# echo "void print_int(int x){ printf(\"%d\n\",x);}" >> "_temp.c"
# cat $1 >> "_temp.c"
# gcc -S -O3 "_temp.c" -o file.s
./Bash/finalproject-cpp.sh $1 $2
# ./Bash/finalproject-py.sh $1