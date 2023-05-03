#ifndef STRING_UTILS_H
#define STRING_UTILS_H

void lowercase_string(char const* original_string, char* lowercased_string);
void alloc_str_and_copy(char** dest, char const* source);
void remove_new_line_char(char* line);

#endif