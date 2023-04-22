#include "line_scanner.h"
#include "args_parser.h"
#include <string.h>
#include <stdlib.h>

bool is_regex_match_in_line(input_line_t* line, arguments_t* arguments) {
    return false;
    // TODO complete
}

bool is_match_in_line(input_line_t* line, arguments_t* arguments) {
    bool is_match = false;
    char * line_to_check = line->line_buffer;
    char * lowercase_string_buffer = NULL;
    printf("original line is %s", line->line_buffer);
    printf("original search pattern is %s\n", arguments->search_pattern);

    if (arguments->ignore_case) {
        lowercase_string_buffer = (char *) malloc (strlen(line->line_buffer) + 1);
        line_to_check = lowercase_string_buffer;
        lowercase_string(line->line_buffer, line_to_check);
        printf("new line is %s", line->line_buffer);
        printf("new search pattern is %s\n", arguments->search_pattern);
    }

    if (arguments->regex_pattern != NULL) {
        is_match = is_regex_match_in_line(line, arguments);
    }
    else if (arguments->line_strict_match) {
        if (strcmp(line_to_check, arguments->search_pattern) == 0) {
            is_match = true;
        }
    }
    else if (strstr(line_to_check, arguments->search_pattern) != NULL) {
        is_match = true;
    }
    if (lowercase_string_buffer != NULL) {
        free(lowercase_string_buffer);
    }
    return is_match;
}

bool should_print_line(input_line_t* line, arguments_t* arguments) {
    return (line->is_match && !arguments->print_non_match) ||
            (!line->is_match && arguments->print_non_match);
}

int read_line(input_scanner_t* input_scanner, input_line_t* line) {
    line->offset = input_scanner->current_offset;
    ssize_t res = 0;
    res = getline(&line->line_buffer, &input_scanner->buff_len, input_scanner->input_stream);
    if (res >= 0) {
        input_scanner->current_offset += res;
    }
    return res;
}

void print_line(input_line_t* line, arguments_t* arguments, unsigned int line_number){
    if (arguments->print_line_number) {
        printf("%u%s", line_number, should_print_line(line, arguments) ? ":" : "-");
    }
    if (arguments->print_line_offset) {
        printf("%u%s", line->offset, should_print_line(line, arguments) ? ":" : "-");
    }
    printf("%s", line->line_buffer);
}

