#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include "string_utils.h"

#define NOT_MATCH_NUM  UINT_MAX

void lowercase_string(char const* original_string, char* lowercased_string) {
    for (unsigned int i = 0; i < strlen(original_string); i++){
        lowercased_string[i] = tolower(original_string[i]);
    }
    lowercased_string[strlen(original_string)] = '\0';
}

void alloc_str_and_copy(char** dest, char const* source) {
    *dest = (char*) malloc(strlen(source) + 1);
    assert(*dest != NULL);
    strcpy(*dest, source);
}

void remove_new_line_char(char* line) {
    int line_length = strlen(line);
    if (line_length > 0 && line[line_length - 1] == '\n') {
        line[line_length - 1] = '\0';
    }
}

bool are_option_chars_indexes_found(char *pattern, unsigned int *indexes_arr) {
    for (unsigned int i = 0; i < strlen(pattern); i++) {
        if (pattern[i] == '(') {
            indexes_arr[0] = i;
        } else if (pattern[i] == '|') {
            indexes_arr[1] = i;
        } else if (pattern[i] == ')') {
            indexes_arr[2] = i;
        }
    }
    return indexes_arr[0] != NOT_MATCH_NUM;
}