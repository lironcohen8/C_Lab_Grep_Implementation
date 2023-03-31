#! /usr/bin/env tcsh

./my_grep Holmes ./my_test_input.txt | diff ./my_test_output.txt -

valgrind --quiet --leak-check=yes ./my_grep Holmes ./my_test_input.txt | diff ./my_test_output.txt -
