#include "line_scanner.h"

int read_line(input_scanner_t* input_scanner, input_line_t* line) {
    line->offset = input_scanner->current_offset;
    size_t len = 0;
    ssize_t res = 0;
    res = getline(&line->line_buffer, &len, input_scanner->input_stream);
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