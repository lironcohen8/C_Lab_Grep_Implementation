#ifndef LINE_SCANNER_H
#define LINE_SCANNER_H

#include <stdbool.h>
#include <stdio.h>
#include "args_parser.h"
#include "input_scanner.h"

typedef struct {
    char* line_buffer;
    unsigned int offset;
    bool is_match;
} input_line_t;

int read_line(input_scanner_t* input_scanner, input_line_t* line);
void print_line(input_line_t* line, arguments_t* argument, unsigned int line_number);

#endif