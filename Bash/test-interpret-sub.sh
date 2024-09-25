#!/bin/bash

_cfilename="${1:-file.c}"
_jsonfilename="${_cfilename%".c"}.json"

cd ../..

touch TestFiles/_test.c
touch TestFiles/_res1.txt
touch TestFiles/_res2.txt

echo "#include <stdio.h>"       >  TestFiles/_test.c
echo ""                         >> TestFiles/_test.c
echo "void print(int a){"       >> TestFiles/_test.c
echo "    printf(\"%d\n\", a);" >> TestFiles/_test.c
echo "}"                        >> TestFiles/_test.c
cat $_cfilename                 >> TestFiles/_test.c
gcc TestFiles/_test.c -o TestFiles/_test
rm TestFiles/_test.c

./TestFiles/_test                   > TestFiles/_res1.txt
./ParserLexer/expr2json.exe "$_cfilename"  >> log.txt
./Interpreter/build/main $_jsonfilename > TestFiles/_res2.txt

# exit 0


if diff TestFiles/_res1.txt TestFiles/_res2.txt; then
    echo "Test passed"
    exit 0
else
    echo "Test failed"
    exit 1
fi

exit 0 