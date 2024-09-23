dune build --root ParserLexer
./ParserLexer/expr2json.exe TestFiles/variable.c
cmake TestFiles -B TestFiles/build
cmake --build TestFiles/build
ctest --test-dir TestFiles/build
cmake Interpreter -B Interpreter/build
make -C Interpreter/build/
./Interpreter/build/main TestFiles/variable.json