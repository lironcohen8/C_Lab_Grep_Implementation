#! /usr/bin/env bash

PROG_NAME=my_grep
GREP_PROGRAM=grep
TESTS_OUTPUT_DIR=test_results
TEST_NUM=1

execute_test() {
    OUTFILE=./$TESTS_OUTPUT_DIR/"test$TEST_NUM.out"
    echo "Running test"$TEST_NUM
    $GREP_PROGRAM $1 > $OUTFILE

    "./$PROG_NAME" $1 | diff $OUTFILE -

    valgrind --quiet --leak-check=yes --track-origins=yes "./$PROG_NAME" $1 | diff $OUTFILE -
    echo "test$TEST_NUM completed"
    TEST_NUM=$((TEST_NUM+1))
}

rm -rf ./$TESTS_OUTPUT_DIR
mkdir ./$TESTS_OUTPUT_DIR

execute_test "arg -n -b main.c" 
execute_test "er.h main.c"
execute_test "ARG -i -n main.c"
execute_test "ARG -i -c main.c"
execute_test "ARG -i -x -c main.c" 
execute_test "ARG -i -x -n main.c"
execute_test "ARG -x main.c"
execute_test "ARG -x -c main.c"
execute_test "ARG -x -n main.c"
execute_test "{ -x main.c"
execute_test "{ -x -c main.c"
execute_test "{ -x -n main.c"
execute_test "arg -n -b main.c"
execute_test "er.h main.c"
execute_test "ARG -i -v -n main.c"
execute_test "ARG -i -v -c main.c"
execute_test "ARG -i -v -x -c main.c"
execute_test "ARG -i -v -x -n main.c"
execute_test "ARG -x -v main.c"
execute_test "ARG -x -c -v main.c"
execute_test "ARG -x -n -v main.c"
execute_test "{ -x -v main.c"
execute_test "{ -x -c -v main.c"
execute_test "{ -x -n -v main.c"
execute_test "ARG -n -A 2 main.c"
execute_test "{ -A 1 main.c"
execute_test "ARG -i -A 2 -c main.c"
execute_test "ARG -i -v -c -A 2 main.c"

NUMBER_TEST_FILE=./$TESTS_OUTPUT_DIR/test_number_file.txt
python3 -c 'for i in range(300):print(f"[{i}]")' > $NUMBER_TEST_FILE

execute_test "7 -A 2 $NUMBER_TEST_FILE"

# regex tests
# ./regex_test1.sh
