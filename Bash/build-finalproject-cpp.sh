#!/bin/bash

cmake Interpreter -B Interpreter/build  >> log.txt
make -C Interpreter/build/  >> log.txt