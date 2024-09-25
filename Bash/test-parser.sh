#!/bin/bash

cmake TestFiles -B TestFiles/build -D mode=dune \
  && cmake --build TestFiles/build \
  && ctest --test-dir TestFiles/build