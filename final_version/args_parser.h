#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <stdbool.h>

typedef struct _arguments_t {
  bool separator_required;
  unsigned int num_lines_after_match;
  bool print_line_offset;
  bool print_count_lines;
  bool ignore_case;
  bool print_line_number;
  bool print_non_match;
  bool line_strict_match;
  char const* input_filename;
  char* search_pattern;
} arguments_t;

void parse_arguments(int argc, char const* argv[], arguments_t* arguments);
void free_args_internals(arguments_t* arguments);

#endif