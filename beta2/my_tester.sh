#! /usr/bin/env bash

PROG_NAME=my_grep
GREP_PROGRAM=grep
TESTS_OUTPUT_DIR=test_results

execute_test() {
    OUTFILE=./$TESTS_OUTPUT_DIR/"test$2.out"
    echo "Running test"$2
    $GREP_PROGRAM $1 > $OUTFILE

    "./$PROG_NAME" $1 | diff $OUTFILE -

    valgrind --quiet --leak-check=yes --track-origins=yes "./$PROG_NAME" $1 | diff $OUTFILE -
    echo "test$2 completed"
}

rm -rf ./$TESTS_OUTPUT_DIR
mkdir ./$TESTS_OUTPUT_DIR

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
execute_test "ARG -n -A 2 main.c" 25
execute_test "{ -A 1 main.c" 26
execute_test "ARG -i -A 2 -c main.c" 27
execute_test "ARG -i -v -c -A 2 main.c" 28

# regex tests
# ./regex_test1.sh
