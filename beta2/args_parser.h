#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <stdbool.h>

typedef struct _pattern_t {
    char const* pattern;
    char * pattern_in_lowercase;
} pattern_t;

typedef struct _arguments_t {
    unsigned int num_lines_after_match;
    bool         print_line_offset;
    bool         print_count_lines;
    bool         ignore_case;
    bool         print_line_number;
    bool         print_non_match;
    bool         line_strict_match;
    pattern_t*   regex_pattern;
    pattern_t*   search_pattern;
    char const*  input_filename;
} arguments_t;


void lowercase_string(char const *original_string, char *lowercased_string);

void parse_arguments(int argc, char const *argv[], arguments_t* arguments);

#endif