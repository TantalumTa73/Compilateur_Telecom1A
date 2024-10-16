dune build
./expr2json.exe ../TestC/operation.c 
cat ../TestC/operation.json | jq --indent 4