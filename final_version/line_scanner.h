#ifndef LINE_SCANNER_H
#define LINE_SCANNER_H

#include "args_parser.h"
#include "input_scanner.h"
#include <stdbool.h>

typedef struct _input_line_t {
  char* line_buffer;
  unsigned int offset;
  bool is_match;
  unsigned int line_num;
  bool include_seperator;
} input_line_t;

bool is_match_in_line(input_line_t* line, arguments_t* arguments, regex_t* regex);
bool should_print_line(arguments_t* arguments, input_scanner_t* input_scanner, input_line_t* line);
bool should_include_separator(bool prev_line_printed, bool current_line_match, bool found_match_yet);
int read_line(input_scanner_t* input_scanner, input_line_t* line);
void print_line(input_line_t* line, arguments_t* arguments);

#endif