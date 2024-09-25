#!/bin/bash

cmake TestFiles -B TestFiles/build
cmake --build TestFiles/build
ctest --test-dir TestFiles/build