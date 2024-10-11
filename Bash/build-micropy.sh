#!/bin/bash

cmake MicroPyCpp -B MicroPyCpp/build  >> log.txt
make -C MicroPyCpp/build/  >> log.txt