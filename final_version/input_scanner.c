#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_scanner.h"
#include "line_scanner.h"

/* private functions */
FILE* get_input_stream(char const* input_filename) {
    if (input_filename == NULL) {
        return stdin;
    }

    FILE* input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        printf("failed to open file %s\n", input_filename);
        exit(EXIT_FAILURE);
    } else {
        return input_file;
    }
}

/* public functions */
void init_input_scanner(input_scanner_t* input_scanner, arguments_t* arguments) {
    input_scanner->current_offset = 0;
    input_scanner->input_stream = get_input_stream(arguments->input_filename);
    input_scanner->buff_len = 0;
    compile_regex(arguments->search_pattern, strlen(arguments->search_pattern), &input_scanner->regex);
    input_scanner->found_match_yet = false;
    input_scanner->number_of_matched_lines = 0;
    input_scanner->last_matched_line_num = 0;
}

void scan_input(input_scanner_t* input_scanner, arguments_t* arguments) {
    input_line_t current_line = {.is_match = false, .line_buffer=NULL, .offset=0, .line_num = 1};
    bool prev_line_printed = false;

    while ((read_line(input_scanner, &current_line)) != -1) {
        current_line.is_match = is_match_in_line(&current_line, arguments, &input_scanner->regex);
        if (arguments->separator_required) {
            current_line.include_seperator = should_include_separator(prev_line_printed,
                current_line.is_match,
                input_scanner->found_match_yet);
        }
        if (current_line.is_match) {
            input_scanner->found_match_yet = true;
            input_scanner->last_matched_line_num = current_line.line_num;
            input_scanner->number_of_matched_lines++;
        }
        if ((prev_line_printed=should_print_line(arguments, input_scanner, &current_line))) {
            print_line(&current_line, arguments);
        }
        current_line.line_num++;
    }

    if (arguments->print_count_lines) {
        printf("%d\n", input_scanner->number_of_matched_lines);
    }
    if (current_line.line_buffer != NULL) {
        free(current_line.line_buffer);
    }
    if (arguments->input_filename != NULL) {
        fclose(input_scanner->input_stream);
    }
}

void free_input_scanner_internals(input_scanner_t* input_scanner) {
    free_regex(&input_scanner->regex);
}