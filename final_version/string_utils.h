#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdbool.h>

#define NO_MATCH UINT_MAX

void lowercase_string(char const* original_string, char* lowercased_string);
void alloc_str_and_copy(char** dest, char const* source);
void remove_new_line_char(char* line);
unsigned int first_index_of_char(char* str, char char_to_look);

#endif