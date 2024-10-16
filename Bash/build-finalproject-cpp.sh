#!/bin/bash

cmake FinalProjectCpp -B FinalProjectCpp/build  >> log.txt
make -C FinalProjectCpp/build/  >> log.txt