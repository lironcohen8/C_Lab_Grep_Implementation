#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <stdbool.h>
#include <stdio.h>

typedef struct _arguments_t {
    unsigned int num_lines_after_match;
    bool         print_line_offset;
    bool         print_count_lines;
    bool         ignore_case;
    bool         print_line_number;
    bool         print_non_match;
    bool         line_strict_match;
    char const*  regex_pattern;
    FILE*        input_stream;
    char const*  search_pattern;
} arguments_t;

void init_arguments(arguments_t* arguments);
void parse_arguments(int argc, char const *argv[], arguments_t* arguments);

#endif