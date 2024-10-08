#!/bin/bash

set -e

file="${1:-file.c}"
filename=$(basename $file ".c")
cfilename=$(basename $file)
pathname=$(dirname $file)
jsonname="${filename}.json"
newcfilename="${pathname}/_tmp/${filename}.cpp"

# echo "file: $file"
# echo "pathname: $pathname"
# echo "cfilename: $cfilename"
# echo "jsonname: $jsonname"
# echo "test path: $newcfilename"

mkdir -p $pathname/_tmp
touch $newcfilename


echo "#include <stdio.h>"       >  $newcfilename
echo "#pragma GCC diagnostic ignored \"-Wmain\""       >>  $newcfilename
echo ""                         >> $newcfilename
echo "void print(int a){"       >> $newcfilename
echo "    printf(\"%d\n\", a);" >> $newcfilename
echo "}"                        >> $newcfilename
echo ""                         >> $newcfilename
echo "void read(int& a){"       >> $newcfilename
echo "    scanf(\"%d\n\",&a);"  >> $newcfilename
echo "}"                        >> $newcfilename
cat $file                       >> $newcfilename
gcc $newcfilename -o $pathname/_tmp/$filename
