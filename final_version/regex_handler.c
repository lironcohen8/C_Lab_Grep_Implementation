#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "regex_handler.h"
#include "string_utils.h"
#include <assert.h>

#define REGEX_ESCAPING_CHAR      '\\'
#define REGEX_DOT_CHAR           '.'
#define REGEX_OPEN_RANGE_CHAR    '['
#define REGEX_CLOSE_RANGE_CHAR   ']'
#define REGEX_OPEN_OPTIONS_CHAR  '('
#define REGEX_CLOSE_OPTIONS_CHAR ')'
#define REGEX_DELIM_OPTIONS_CHAR '|'
#define NUMBER_OF_OPTIONS_CHARS   REGEX_NUMBER_OF_STRING_OPTIONS + 1

bool match_regex_from_base(char* str_to_match, regex_element_t* regex_element, int elements_remained);

/* private functions */
unsigned int min_len_option(regex_element_t* element) {
    unsigned int min_len = UINT_MAX, curr_len = 0;
    for (int i = 0 ; i < REGEX_NUMBER_OF_STRING_OPTIONS ; i++) {
        curr_len = element->options[i].len;
        if (curr_len < min_len) {
            min_len = curr_len;
        }
    }
    return min_len;
}

unsigned int min_num_chars_required_to_match(regex_t* regex) {
    unsigned int total_min_len = 0;
    unsigned int element_min_len = 0;
    for (unsigned int elemnt_idx = 0; elemnt_idx < regex->len; elemnt_idx++) {
        if (regex->element_arr[elemnt_idx].type != OPTIONS) {
            element_min_len = 1;
        } else {
            element_min_len = min_len_option(&regex->element_arr[elemnt_idx]);
        }
        total_min_len += element_min_len;
    }
    return total_min_len;
}

void get_options_element_indexes(char* pattern, unsigned int* indexes) {
    indexes[0] = first_index_of_char(pattern, REGEX_OPEN_OPTIONS_CHAR);
    indexes[1] = first_index_of_char(pattern, REGEX_DELIM_OPTIONS_CHAR);
    indexes[2] = first_index_of_char(pattern, REGEX_CLOSE_OPTIONS_CHAR);
}

unsigned int regex_build_options_element(char* pattern, regex_element_t* element) {
    unsigned int indexes_arr[NUMBER_OF_OPTIONS_CHARS] = {NO_MATCH, NO_MATCH, NO_MATCH};
    get_options_element_indexes(pattern, indexes_arr);
    element->type = OPTIONS;
    for (int i = 0 ; i < REGEX_NUMBER_OF_STRING_OPTIONS ; i++) {
        int option_len = indexes_arr[i+1] - indexes_arr[i] - 1;
        compile_regex(&pattern[indexes_arr[i] + 1], option_len, &element->options[i]);
    }
    return indexes_arr[NUMBER_OF_OPTIONS_CHARS - 1] - indexes_arr[0] + 1;
}

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
    } else if (pattern[0] == REGEX_OPEN_OPTIONS_CHAR) {
        chars_processed = regex_build_options_element(pattern, element);
    } else {
        element->type = SIMPLE_CHAR;
        element->simple_char = pattern[0];
        chars_processed = 1;
    }
    return chars_processed;
}

void match_regex_element(char* str_to_match, regex_element_t* regex_element, unsigned int num_matched_chars[REGEX_NUMBER_OF_STRING_OPTIONS]) {
    switch (regex_element->type) {
        case SIMPLE_CHAR:
            num_matched_chars[0] = (str_to_match[0] == regex_element->simple_char);
            break;
        case DOT:
            num_matched_chars[0] = 1;
            break;
        case RANGE:
            num_matched_chars[0] = (str_to_match[0] >= regex_element->range.start &&
                                    str_to_match[0] <= regex_element->range.end);
            break;
        case OPTIONS:
            for (int i = 0 ; i < REGEX_NUMBER_OF_STRING_OPTIONS ; i++) {
                regex_t* option = &regex_element->options[i];
                if (match_regex_from_base(str_to_match, option->element_arr, option->len)) {
                    num_matched_chars[i] = option->len;
                }
            }
            break;
    }
}

bool match_regex_from_base(char* str_to_match, regex_element_t* regex_element, int elements_remained) {
    if (elements_remained == 0) {
        return true;
    }
    if (*str_to_match == '\0' && regex_element->type != OPTIONS) {
        return false;
    }
    unsigned int num_matched_chars[REGEX_NUMBER_OF_STRING_OPTIONS] = {NO_MATCH, NO_MATCH};
    match_regex_element(str_to_match, regex_element, num_matched_chars);

    if (regex_element->type != OPTIONS && num_matched_chars[0] == 0) {
        return false;
    }

    if (regex_element->type == OPTIONS && num_matched_chars[0] == NO_MATCH && num_matched_chars[1] == NO_MATCH) {
        return false;
    }

    regex_element++;
    elements_remained--;
    bool match_result[REGEX_NUMBER_OF_STRING_OPTIONS] = {false,false};

    for (int i = 0; i < REGEX_NUMBER_OF_STRING_OPTIONS; i++) {
        if (num_matched_chars[i] != NO_MATCH && num_matched_chars[i] <= strlen(str_to_match)) {
            match_result[i] = match_regex_from_base(str_to_match + num_matched_chars[i], regex_element, elements_remained);
        }
    }

    return match_result[0] || match_result[1];
}

/* public functions */
void compile_regex(char* pattern, unsigned int pattern_length, regex_t* regex) {
    if (pattern_length > 0) {
        regex->element_arr = (regex_element_t*) malloc (pattern_length * sizeof(regex_element_t));
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
    } else {
        regex->element_arr = NULL;
        regex->len = 0;
    }
}

bool is_regex_match_in_line(char* line, unsigned int str_len, regex_t* regex, bool is_strict) {
    unsigned int min_num_chars_required = min_num_chars_required_to_match(regex);
    if (min_num_chars_required > str_len) {
        return false;
    }
    if (is_strict) {
        // TODO the first condition is not correct for regex
        return (min_num_chars_required == str_len) && match_regex_from_base(line, regex->element_arr, regex->len);
    }
    for (unsigned int i = 0; i <= str_len - min_num_chars_required; i++) {
        if (match_regex_from_base(line, regex->element_arr, regex->len)) {
            return true;
        }
        line++;
    }
    return false;
}

void free_regex(regex_t* regex) {
    for (unsigned int i = 0; i < regex->len; i++) {
        if (regex->element_arr[i].type == OPTIONS) {
            for (int j = 0; j < REGEX_NUMBER_OF_STRING_OPTIONS; j++) {
                free_regex(&regex->element_arr[i].options[j]);
            }
        }
    }
    if (regex->element_arr != NULL) {
        free(regex->element_arr);
    }
}