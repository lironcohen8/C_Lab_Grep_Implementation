#include <stdlib.h>
#include <string.h>
#include "regex_handler.h"
#include "assert.h"

#define REGEX_ESCAPING_CHAR    '\\'
#define REGEX_DOT_CHAR         '.'
#define REGEX_OPEN_RANGE_CHAR  '['
#define REGEX_CLOSE_RANGE_CHAR ']'

/* private functions */
unsigned int process_regex_element(char* pattern, regex_element_t* element) {
    unsigned int chars_processed = 0;
    if (pattern[0] == REGEX_ESCAPING_CHAR) {
        element->type = SIMPLE_CHAR;
        element->simple_char = pattern[1];
        chars_processed = 2;
    } else if (pattern[0] == REGEX_DOT_CHAR) {
        element->type = DOT;
        chars_processed = 1;
    } else if (pattern[0] == REGEX_OPEN_RANGE_CHAR && pattern[4] == REGEX_CLOSE_RANGE_CHAR) {
        element->type = RANGE;
        element->range.start = pattern[1];
        element->range.end = pattern[3];
        chars_processed = 5;
    } else {
        element->type = SIMPLE_CHAR;
        element->simple_char = pattern[0];
        chars_processed = 1;
    }
    return chars_processed;
}

bool match_regex_element(char* str_to_match, regex_element_t* regex_element) {
    switch (regex_element->type) {
        case SIMPLE_CHAR:
            return str_to_match[0] == regex_element->simple_char;
        case DOT:
            return true;
        case RANGE:
            return str_to_match[0] >= regex_element->range.start &&
                   str_to_match[0] <= regex_element->range.end;
        case RECURSIVE:
            return false;
    }
    return false;
}

void compile_regex(char* pattern, regex_t* regex) {
    unsigned int pattern_length = strlen(pattern);
    regex->element_arr = (regex_element_t*) malloc(pattern_length * sizeof(regex_element_t));
    assert(regex->element_arr != NULL);
    unsigned int chars_processed = 0, chars_processed_in_iteration = 0;
    unsigned int current_elemnet_idx = 0;
    while (chars_processed < pattern_length) {
        chars_processed_in_iteration = process_regex_element(pattern, &regex->element_arr[current_elemnet_idx]);
        chars_processed += chars_processed_in_iteration;
        pattern += chars_processed_in_iteration;
        current_elemnet_idx++;
    }
    regex->element_arr = (regex_element_t*)realloc(regex->element_arr, (current_elemnet_idx) * sizeof(regex_element_t));
    assert(regex->element_arr != NULL);
    regex->len = current_elemnet_idx;
}

bool match_regex_from_base(char* str_to_match, regex_t* regex) {
    for (unsigned int i = 0; i < regex->len; i++) {
        if (!match_regex_element(str_to_match, &regex->element_arr[i])) {
            return false;
        }
        str_to_match++;
    }
    return true; 
}

/* public functions */
bool is_regex_match_in_line(char* line, unsigned int str_len, regex_t* regex, bool is_strict) {
    if (regex->len > str_len) {
        return false;
    }
    if (is_strict) {
        return (regex->len == str_len) && match_regex_from_base(line, regex);
    }
    for (unsigned int i = 0; i <= str_len - regex->len; i++) {
        if (match_regex_from_base(line, regex)) {
            return true;
        }
        line++;
    }
    return false;
}

void free_regex(regex_t* regex) {
    if (regex->element_arr != NULL) {
        free(regex->element_arr);
    }
}