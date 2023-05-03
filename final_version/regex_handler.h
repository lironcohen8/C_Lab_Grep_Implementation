#ifndef REGEX_HANDLER_H
#define REGEX_HANDLER_H
#define REGEX_NUMBER_OF_STRING_OPTIONS 2

#include <stdbool.h>

typedef enum {
    SIMPLE_CHAR,
    RANGE,
    DOT,
    OPTIONS,
} regex_type_e;

typedef struct {
    char start;
    char end;
} regex_range_t;

typedef struct {
    regex_type_e type;
    union {
        char                   simple_char;
        regex_range_t          range;
        regex_string_options_t options;
    };
} regex_element_t;

typedef struct {
    unsigned int len;
    regex_element_t* element_arr;
} regex_t;

typedef struct {
    regex_t options[REGEX_NUMBER_OF_STRING_OPTIONS];
} regex_string_options_t;

bool is_regex_match_in_line(char* line, unsigned int str_len, regex_t* regex, bool is_strict);
void compile_regex(char* pattern, regex_t* regex);
void free_regex(regex_t* regex);

#endif