#! /usr/bin/env bash

PROG_NAME=my_grep
GREP_PROGRAM=grep

execute_test() {
    $GREP_PROGRAM $1 > $2

    "./$PROG_NAME" $1 | diff $2 -

    valgrind --quiet --leak-check=yes "./$PROG_NAME" $1 | diff $2 -
}

execute_test "arg -n -b main.c" "test1.out"