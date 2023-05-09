#! /usr/bin/env tcsh

grep -n -i -E 'er\.h' main.c > test_regex1

./my_grep -n -i -E 'er\.h' main.c | diff test_regex1 -

valgrind --quiet --leak-check=yes ./my_grep -n -i -E 'er\.h' main.c | diff test_regex1 -


grep -n -b -E '\[1.1\]' test_results/test_number_file.txt > test_regex2

./my_grep -n -b -E '\[1.1\]' test_results/test_number_file.txt | diff test_regex2 -

valgrind --quiet --leak-check=yes ./my_grep -n -b -E '\[1.1\]' test_results/test_number_file.txt | diff test_regex2 -


grep -n -b -A 3 -E '\[(1|3).(2|4)\]' test_results/test_number_file.txt > test_regex3

./my_grep -n -b -A 3 -E '\[(1|3).(2|4)\]' test_results/test_number_file.txt | diff test_regex3 -

valgrind --quiet --leak-check=yes ./my_grep -n -b -A 3 -E '\[(1|3).(2|4)\]' test_results/test_number_file.txt | diff test_regex3 -


grep -n -b -A 3 -E '(1|3)(2|4)' test_results/test_number_file.txt > test_regex4

./my_grep -n -b -A 3 -E '(1|3)(2|4)' test_results/test_number_file.txt | diff test_regex4 -

valgrind --quiet --leak-check=yes ./my_grep -n -b -A 3 -E '(1|3)(2|4)' test_results/test_number_file.txt | diff test_regex4 -
