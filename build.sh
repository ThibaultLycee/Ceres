#!/bin/sh -x

OUT="./comp"

if [ !-d "$OUT" ] ; then
	mkdir $OUT
fi

rm $OUT/ceres
rm $OUT/tests

rm ./tests_out/diff/*

gcc -Wall -Wextra ./main.c -o $OUT/ceres
gcc -Wall -Wextra ./tests.c -o $OUT/tests

$OUT/tests run
