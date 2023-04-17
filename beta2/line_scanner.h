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

bool is_match_in_line(input_line_t* line, arguments_t* arguments);
bool should_print_line(input_line_t* line, arguments_t* arguments);
int read_line(input_scanner_t* input_scanner, input_line_t* line);
void print_line(input_line_t* line, arguments_t* arguments, unsigned int line_number);

#endif