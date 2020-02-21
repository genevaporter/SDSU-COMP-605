#!/bin/bash

gcc -pg ./assignment-1.cpp -o test
./test
gprof./test

valgrind --tool=memcheck --leak-check=yes ./assignment-1.cpp
