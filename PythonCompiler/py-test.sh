cd ..
cd ParserLexer
eval $(opam env)
dune build
./expr2json.exe ../TestFiles/simple.c
cd ..
cd PythonCompiler
python3 compiler.py ../TestFiles/simple.json
gcc ../TestFiles/simple.s -g
./a.out