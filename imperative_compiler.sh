cd ParserLexer
dune build
cd ..
./ParserLexer/_build/default/expr2json.exe TestFiles/variable.c
cmake Interpreter -B Interpreter/build
make -C Interpreter/build/
./Interpreter/build/main TestFiles/variable.json