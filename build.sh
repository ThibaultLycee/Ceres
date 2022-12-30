#!/bin/sh -x

rm ./ceres
rm ./tests

rm ./tests_out/diff/*

gcc -Wall -Wextra ./main.c -o ./ceres
gcc -Wall -Wextra ./tests.c -o ./tests

./tests run
