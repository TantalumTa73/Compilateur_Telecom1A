cd ..
cd ParserLexer
eval $(opam env)
dune build
./expr2json.exe ../TestC/simple.c
cd ..
cd PythonCompiler
python3 compiler.py ../TestC/simple.json
gcc ../TestC/simple.s -g
./a.out