#include <stdio.h>
#include <stdlib.h>
#include "input_scanner.h"
#include "line_scanner.h"

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

void scan_input(arguments_t* arguments) {
    input_scanner_t input_scanner = {.current_offset = 0, .input_stream = NULL, .buff_len = 0};
    input_scanner.input_stream = get_input_stream(arguments->input_filename);
    input_line_t current_line = {.is_match = false, .line_buffer=NULL, .offset=0};
    unsigned int current_line_num = 1;
    unsigned int number_of_matched_lines = 0;

    while ((read_line(&input_scanner, &current_line)) != -1) {
        current_line.is_match = is_match_in_line(&current_line, arguments);
        if (should_use_line(&current_line, arguments)) {
            if (should_print_line(arguments)) {
                print_line(&current_line, arguments, current_line_num);
            }
            number_of_matched_lines++;
        }
        current_line_num++;
    }

    if (arguments->print_count_lines) {
        printf("%d\n", number_of_matched_lines);
    }

    if (current_line.line_buffer != NULL) {
        free(current_line.line_buffer);
    }
    if (arguments->input_filename != NULL) {
        fclose(input_scanner.input_stream);
    }
}