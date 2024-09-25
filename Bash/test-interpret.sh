#!/bin/bash

./Bash/build-dune.sh
./Bash/build-interpret.sh


cmake TestFiles -B TestFiles/build -D mode=interpret \
  && cmake --build TestFiles/build \
  && ctest --test-dir TestFiles/build