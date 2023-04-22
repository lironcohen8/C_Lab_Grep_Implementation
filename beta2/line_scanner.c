#include "line_scanner.h"
#include "args_parser.h"
#include <string.h>

bool is_regex_match_in_line(input_line_t* line, arguments_t* arguments) {
    return false;
    // TODO complete
}

bool is_match_in_line(input_line_t* line, arguments_t* arguments) {
    char * line_to_check = line->line_buffer;
    char * pattern_to_check = arguments->search_pattern->pattern;
    if (arguments->ignore_case) {
        lowercase_string(line->line_buffer, line->line_in_lowercase);
        line_to_check = line->line_in_lowercase;
        pattern_to_check = arguments->search_pattern->pattern_in_lowercase;
    }
    if (arguments->regex_pattern->pattern != NULL) {
        return is_regex_match_in_line(line, arguments);
    }
    if (arguments->line_strict_match) {
        if (strcmp(line_to_check, pattern_to_check) == 0) {
            return true;
        }
        return false;
    }
    if (strstr(line_to_check, pattern_to_check) != NULL) {
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
        printf("%u%s", line_number, should_print_line(line, arguments) ? ":" : "-");
    }
    if (arguments->print_line_offset) {
        printf("%u%s", line->offset, should_print_line(line, arguments) ? ":" : "-");
    }
    printf("%s", line->line_buffer);
}

