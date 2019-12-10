#!/bin/bash

PROG=grpwk
CC=gcc
CFLAGS="-W -Wall -Wextra -Wconversion -Wshadow"
DIR="."
TCASE=0

usage_exit() {
    echo "Usage: $0 [-n (no warning)] [-d <dir name>] [-t <test id>]"
}

while getopts :hnd:t: OPT
do
    case $OPT in
        n) CFLAGS=""
            echo "You are running the compiler withOUT -Wall option!"
            ;;
        d) DIR=$OPTARG;;
        t) TCASE=$OPTARG;;
        h) usage_exit;;
        \?) usage_exit;;
    esac
done
shift $(($OPTIND - 1))

FILES=$(find -maxdepth 1 \( -name "*.c" \) \( -not -name "*test*" \))
MYFILES=$(find $DIR \( -name "*.c" \) \( -not -name "*test*" \))

$CC $CFLAGS -o grpwk $FILES $MYFILES
$CC -o distance test_distance.c

echo -------------result
echo -n "time         : "
./grpwk data/dat${TCASE}_in result
./distance result data/dat${TCASE}_ref

rm distance
rm grpwk

# echo
# echo -------------output
# cat result
