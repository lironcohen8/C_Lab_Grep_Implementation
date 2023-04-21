CFLAGS = -g -Wall -Wextra
PROGRAM = my_grep
CC = gcc
GREP_TESTS_FOLDER = /a/home/cc/students/csguests/nimrodav/grep_tests

$(PROGRAM): main.o input_scanner.o args_parser.o line_scanner.o
	$(CC) -o $@ $^ $(CFLAGS)

main.o: args_parser.h input_scanner.h

args_parser.o: args_parser.h

input_scanner.o: input_scanner.h line_scanner.h

line_scanner.o: line_scanner.h

.PHONY: clean all test our_test

all: $(PROGRAM)

clean:
	-rm *.o $(PROGRAM)

test:
	$(GREP_TESTS_FOLDER)/beta2.sh

our_test:
	./my_tester.sh