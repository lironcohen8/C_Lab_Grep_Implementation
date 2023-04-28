#ifndef INPUT_SCANNER_H
#define INPUT_SCANNER_H

#include <stdio.h>
#include "args_parser.h"
#include "regex_parser.h"

typedef struct {
    FILE*         input_stream;
    unsigned int  current_offset;
    size_t        buff_len;
    regex_t       regex;
    bool          found_match_yet;
    unsigned int  number_of_matched_lines;
    unsigned int  last_matched_line_num;
} input_scanner_t;

void init_input_scanner(input_scanner_t* input_scanner, arguments_t* arguments);
void scan_input(input_scanner_t* input_scanner, arguments_t* arguments);
void free_input_scanner_internals(input_scanner_t* input_scanner);

#endif