#!/bin/bash

cmake TestC -B TestC/build -D mode=dune \
  && cmake --build TestC/build \
  && ctest --test-dir TestC/build