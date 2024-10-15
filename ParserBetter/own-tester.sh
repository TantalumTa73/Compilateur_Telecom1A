dune build
./expr2json.exe ../TestFiles/operation.c 
cat ../TestFiles/operation.json | jq --indent 4