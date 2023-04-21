#! /usr/bin/env bash

PROG_NAME=my_grep
GREP_PROGRAM=grep

execute_test() {
    OUTFILE="test"$2.out
    echo "Running test"$2
    $GREP_PROGRAM $1 > $OUTFILE

    "./$PROG_NAME" $1 | diff $OUTFILE -

    valgrind --quiet --leak-check=yes "./$PROG_NAME" $1 | diff $OUTFILE -
    echo "test$2 completed"
}

execute_test "arg -n -b main.c" 1
execute_test "er.h main.c" 2
execute_test "ARG -i -n main.c" 3
execute_test "ARG -i -c main.c" 4


# regex tests
./regex_test1.sh
