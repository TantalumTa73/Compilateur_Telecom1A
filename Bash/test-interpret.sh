#!/bin/bash

./Bash/build-dune.sh
./Bash/build-interpret.sh


cmake TestC -B TestC/build -D mode=interpret \
  && cmake --build TestC/build \
  && ctest --test-dir TestC/build