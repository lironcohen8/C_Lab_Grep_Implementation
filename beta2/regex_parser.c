#include <stdlib.h>
#include <string.h>
#include "regex_parser.h"
#include "assert.h"

#define REGEX_ESCAPING_CHAR   '\\'
#define REGEX_DOT_CHAR        '.'
#define REGEX_OPEN_RANGE      '['
#define REGEX_CLOSE_RANGE     ']'

/* private functions */
unsigned int get_regex_element(char* pattern, regex_element_t* element) {
    if (pattern[0] == REGEX_ESCAPING_CHAR) {
        element->type = SIMPLE_CHAR;
        element->simple_char = pattern[1];
        return 2;
    }
    if (pattern[0] == REGEX_DOT_CHAR) {
        element->type = DOT;
        return 1;
    }
    if (pattern[0] == REGEX_OPEN_RANGE && pattern[4] == REGEX_CLOSE_RANGE) {
        element->type = RANGE;
        element->range.end = pattern[1];
        element->range.start = pattern[2];
        return 5;
    }
    // todo more here
    element->type = SIMPLE_CHAR;
    element->simple_char = pattern[0];
    return 1;
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
            // todo in the final version
            return false;
    }
    return false;
}

void compile_regex(char* pattern, unsigned int pattern_length, regex_t* regex) {
    regex->element_arr = (regex_element_t*) malloc(pattern_length * sizeof(regex_element_t));
    assert(regex->element_arr != NULL);
    unsigned int chars_processed = 0, chars_processed_in_iteration = 0;
    unsigned int current_elemnt_index = 0;
    while (chars_processed < pattern_length) {
        chars_processed_in_iteration = get_regex_element(pattern, &regex->element_arr[current_elemnt_index]);
        chars_processed += chars_processed_in_iteration;
        pattern += chars_processed_in_iteration;
        current_elemnt_index++;
    }
    regex->element_arr = (regex_element_t*)realloc(regex->element_arr, (current_elemnt_index) * sizeof(regex_element_t));
    assert(regex->element_arr != NULL);
    regex->len = current_elemnt_index;
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

bool match_regex_in_str(char* str_to_match, unsigned int str_len, regex_t* regex) {
    if (regex->len > str_len) {
        return false;
    }
    for (unsigned int i = 0; i <= str_len - regex->len; i++) {
        if (match_regex_from_base(str_to_match, regex)) {
            return true;
        }
        str_to_match++;
    }
    return false;
}

bool is_regex_match_in_line(char* line, char* regex_pattern) {
    regex_t regex;
    bool is_match = false;
    compile_regex(regex_pattern , strlen(regex_pattern), &regex);
    is_match = match_regex_in_str(line, strlen(line), &regex);
    free(regex.element_arr);
    return is_match;
}