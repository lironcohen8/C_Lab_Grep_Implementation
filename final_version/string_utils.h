#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdbool.h>

void lowercase_string(char const* original_string, char* lowercased_string);
void alloc_str_and_copy(char** dest, char const* source);
void remove_new_line_char(char* line);
bool are_option_chars_indexes_found(char *pattern, unsigned int *indexes_arr);

#endif