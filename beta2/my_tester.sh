#! /usr/bin/env bash

PROG_NAME=my_grep
GREP_PROGRAM=grep

execute_test() {
    OUTFILE="test"$2.out
    echo "Running test"$2
    $GREP_PROGRAM $1 > $OUTFILE

    "./$PROG_NAME" $1 | diff $OUTFILE -

    valgrind --quiet --leak-check=yes "./$PROG_NAME" $1 | diff $OUTFILE -
    #echo "test$2 completed"
}

execute_test "arg -n -b main.c" 1
execute_test "er.h main.c" 2
execute_test "ARG -i -n main.c" 3
execute_test "ARG -i -c main.c" 4
execute_test "ARG -i -x -c main.c" 5
execute_test "ARG -i -x -n main.c" 6
execute_test "ARG -x main.c" 7
execute_test "ARG -x -c main.c" 8
execute_test "ARG -x -n main.c" 9
execute_test "{ -x main.c" 10
execute_test "{ -x -c main.c" 11
execute_test "{ -x -n main.c" 12
execute_test "arg -n -b main.c" 13
execute_test "er.h main.c" 14
execute_test "ARG -i -v -n main.c" 15
execute_test "ARG -i -v -c main.c" 16
execute_test "ARG -i -v -x -c main.c" 17
execute_test "ARG -i -v -x -n main.c" 18
execute_test "ARG -x -v main.c" 19
execute_test "ARG -x -c -v main.c" 20
execute_test "ARG -x -n -v main.c" 21
execute_test "{ -x -v main.c" 22
execute_test "{ -x -c -v main.c" 23
execute_test "{ -x -n -v main.c" 24

# regex tests
# ./regex_test1.sh
