#!/bin/bash

cmake Compiler -B Compiler/build  >> log.txt
make -C Compiler/build/  >> log.txt