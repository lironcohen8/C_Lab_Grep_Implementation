#include "line_scanner.h"
#include <string.h>

bool is_match_in_line(input_line_t* line, arguments_t* arguments) {
    // TODO : a lot here ...
    if (strstr(line->line_buffer, arguments->search_pattern) != NULL) {
        return true;
    }
    
    return false;
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
        printf("%u%s", line_number, line->is_match ? ":" : "-");
    }
    if (arguments->print_line_offset) {
        printf("%u%s", line->offset, line->is_match ? ":" : "-");
    }
    printf("%s", line->line_buffer);
}