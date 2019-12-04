#!/bin/bash

PROG=grpwk
CC=gcc
CFLAGS="-W -Wall -Wextra -Wconversion -Wshadow"
DIR="."
ID=0

usage_exit() {
    echo "Usage: $0 [-n (no warning)] [-d <dir name>] [-t <test id>]"
}

while getopts :hnd:t: OPT
do
    case $OPT in
        n) CFLAGS="";;
        d) DIR=$OPTARG;;
        t) ID=$OPTARG;;
        h) usage_exit;;
        \?) usage_exit;;
    esac
done
shift $(($OPTIND - 1))

FILES=$(find -maxdepth 1 \( -name "*.c" \) \( -not -name "*test*" \))
TEST=$(find $DIR \( -name "*.c" \) \( -not -name "*test*" \))

$CC $CFLAGS -o grpwk $FILES $TEST
$CC -o distance test_distance.c

echo -------------result
echo -n "time         : "
./grpwk data/dat${ID}_in result
./distance result data/dat${ID}_ref

rm distance
rm grpwk

echo -------------output
cat result
