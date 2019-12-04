#!/bin/bash

PROG=grpwk
CC=gcc
CFLAGS="-W -Wall -Wextra -Wconversion -Wshadow"

FILES=$(find -maxdepth 1 \( -name "*.c" \) \( -not -name "*test*" \))
TEST=$(find $1 \( -name "*.c" \) \( -not -name "*test*" \))
$CC $CFLAGS -o grpwk $FILES $TEST
$CC -o distance test_distance.c

echo -------------result
echo -n "time         : "
./grpwk data/dat$2_in result
./distance result data/dat$2_ref

echo -------------output
cat result
