#!/bin/bash

set -e

file="${1:-file.c}"
file_name=$(basename $file ".c")
path_name=$(dirname $file)
c_file=$path_name/$file_name.c
json_file="$path_name/$file_name.json"
gcc_file="${path_name}/_tmp/${file_name}.cpp"
gcc_exe="${path_name}/_tmp/${file_name}"
log_c="${path_name}/_tmp/${file_name}_c.log"
log_gcc="${path_name}/_tmp/${file_name}_gcc.log"

# echo "file: $file"
# echo "file_name: $file_name"
# echo "path_name: $path_name"
# echo "c_file: $c_file"
# echo "json_file: $json_file"
# echo "gcc_file: $gcc_file"
# echo "gcc_exe: $gcc_exe"
# echo "log_c: $log_c"
# echo "log_gcc: $log_gcc"

if [ -z "$2" ]; then
    cd .
else
    cd ../..
fi

mkdir -p ./$pathname/_tmp
touch $log_c
touch $log_gcc


./ParserLexer/expr2json.exe "$path/$c_file" >> log.txt || (echo "ParserLexer failed" ; exit 1)
./Interpreter/build/main "$path/$json_file" < ./TestFiles/_tmp/_value.txt > $log_c   || (echo "Interpreter failed" ; exit 1)
./Bash/interpret-gcc.sh $path/$c_file       >> log.txt || (echo "interpret-gcc failed" ; exit 1)
$gcc_exe < ./TestFiles/_tmp/_value.txt      > $log_gcc || (echo "file return exit error" ;)


if diff $log_c $log_gcc; then
    echo "Test passed"
    exit 0
else
    echo "Test failed"
    exit 1
fi

echo "Test failed"
exit 1