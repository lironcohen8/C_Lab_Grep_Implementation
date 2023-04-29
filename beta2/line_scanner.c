#include "line_scanner.h"
#include "args_parser.h"
#include "regex_handler.h"
#include "string_utils.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define SEPARATOR_LINE "--\n"

bool is_match_in_line(input_line_t* line, arguments_t* arguments, regex_t* regex) {
    bool is_match = false;
    char* line_to_check = line->line_buffer;
    char* lowercase_string_buffer = NULL;

    if (arguments->ignore_case) {
        lowercase_string_buffer = (char*)malloc(strlen(line->line_buffer) + 1);
        assert (lowercase_string_buffer != NULL);
        lowercase_string(line->line_buffer, lowercase_string_buffer);
        line_to_check = lowercase_string_buffer;
    }

    is_match = is_regex_match_in_line(line_to_check, strlen(line_to_check), regex, arguments->line_strict_match);

    if (lowercase_string_buffer != NULL) {
        free(lowercase_string_buffer);
    }
    return (is_match && !arguments->print_non_match) ||
           (!is_match && arguments->print_non_match);
}

bool should_print_line(arguments_t* arguments, input_scanner_t* input_scanner, input_line_t* line) {
    return !arguments->print_count_lines &&
            input_scanner->found_match_yet && 
            line->line_num - input_scanner->last_matched_line_num <= arguments->num_lines_after_match;
}

bool should_include_separator(bool prev_line_printed, bool current_line_match, bool found_match_yet) {
    return !prev_line_printed && current_line_match && found_match_yet;
}

int read_line(input_scanner_t* input_scanner, input_line_t* line) {
    line->offset = input_scanner->current_offset;
    ssize_t res = 0;
    res = getline(&line->line_buffer, &input_scanner->buff_len, input_scanner->input_stream);
    if (res >= 0) {
        input_scanner->current_offset += res;
        remove_new_line_char(line->line_buffer);
    }
    return res;
}

void print_line(input_line_t* line, arguments_t* arguments){
    if (line->include_seperator) {
        printf(SEPARATOR_LINE);
    }
    if (arguments->print_line_number) {
        printf("%u%s", line->line_num, line->is_match ? ":" : "-");
    }
    if (arguments->print_line_offset) {
        printf("%u%s", line->offset, line->is_match ? ":" : "-");
    }
    printf("%s\n", line->line_buffer);
}

