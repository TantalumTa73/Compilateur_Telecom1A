#!/bin/bash

cmake InterpMicroPyCppreter -B MicroPyCpp/build  >> log.txt
make -C MicroPyCpp/build/  >> log.txt