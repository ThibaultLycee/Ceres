#!/bin/sh -x

rm ./comp/ceres
rm ./comp/tests

rm ./tests_out/diff/*

gcc -Wall -Wextra ./main.c -o ./comp/ceres
gcc -Wall -Wextra ./tests.c -o ./comp/tests

./comp/tests run
