#ifndef REGEX_PARSER_H
#define REGEX_PARSER_H

#include <stdbool.h>

typedef enum {
    SIMPLE_CHAR,
    RANGE,
    DOT,
    RECURSIVE,
} regex_type_e;

typedef struct {
    char start;
    char end;
} regex_range_t;

typedef struct {
    regex_type_e type;
    union {
        char          simple_char;
        regex_range_t range;
    };
} regex_element_t;

typedef struct {
    unsigned int len;
    regex_element_t* element_arr;
} regex_t;

bool is_regex_match_in_line(char* line, char* regex_pattern);

#endif