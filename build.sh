#!/bin/sh -x

rm ./build/ceres
rm ./build/tests

rm ./tests_out/diff/*

gcc -Wall -Wextra ./main.c -o ./build/ceres
gcc -Wall -Wextra ./tests.c -o ./build/tests

./build/tests run
