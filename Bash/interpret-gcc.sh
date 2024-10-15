#!/bin/bash

# set -e

file="${1:-file.c}"
filename=$(basename $file ".c")
cfilename=$(basename $file)
pathname=$(dirname $file)
jsonname="${filename}.json"
newcfilename="${pathname}/_tmp/${filename}.c"

# echo "file: $file"
# echo "pathname: $pathname"
# echo "cfilename: $cfilename"
# echo "jsonname: $jsonname"
# echo "test path: $newcfilename"

mkdir -p $pathname/_tmp
touch $newcfilename


echo "#include <stdio.h>"       >  $newcfilename
echo "#pragma GCC diagnostic ignored \"-Wmain\""       >>  $newcfilename

# echo ""                         >> $newcfilename
# echo "void print(int a){"       >> $newcfilename
# echo "    printf(\"%d\n\", a);" >> $newcfilename
# echo "}"                        >> $newcfilename
# echo ""                         >> $newcfilename
# echo "void read(int& a){"       >> $newcfilename
# echo "    scanf(\"%d\n\",&a);"  >> $newcfilename
# echo "}"                        >> $newcfilename

# s1="int"
# s2="scanf(\"%d\\n\",&"
# s2="ant"
# echo "s1: $s1"
# echo "s2: $s2"
# while IFS='' read -r a; do
#     echo "${a//$s1/$s2}"
# done < $file >>  $newcfilename
# out=$(cat $file)
# echo $out >> $newcfilename
# sed 's/read(/scanf(\"%d\\n\",&/g' < $file >>  $newcfilename

echo "#include <stdio.h>"       >  $newcfilename
echo "#pragma GCC diagnostic ignored \"-Wmain\""       >>  $newcfilename

sed 's/read(/scanf(\"%d\",\&/g' < $file >> "${newcfilename}.txt"
sed 's/print(/printf(\"%d\\n\",/g' < "${newcfilename}.txt" >> $newcfilename
rm "${newcfilename}.txt"

echo "gcc c file written"

gcc $newcfilename -o $pathname/_tmp/$filename || (echo "gcc failed" ; exit 1)
