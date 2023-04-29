#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "string_utils.h"

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