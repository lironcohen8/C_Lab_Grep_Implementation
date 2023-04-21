#! /usr/bin/env tcsh

grep -n -i -E 'er\.h' main.c > test_regex1

./my_grep -n -i -E 'er\.h' main.c | diff test_regex1 -

valgrind --quiet --leak-check=yes ./my_grep -n -i -E 'er\.h' main.c | diff test_regex1 -

