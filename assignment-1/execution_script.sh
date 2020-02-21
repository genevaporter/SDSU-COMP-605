#!/bin/bash

gcc -pg ./assignment-1.cpp -o test

# gcc -O3 ...? GCC optimization flags (O0 - no optimization)

./test
gprof./test

valgrind --tool=memcheck --leak-check=yes ./assignment-1.cpp
