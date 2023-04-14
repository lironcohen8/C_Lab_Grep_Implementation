#include "args_parser.h"
#include "stdlib.h"
#include "string.h"

#define LINES_AFTER_MATCH_FLAG 'A'
#define LINE_OFFSET_FLAG       'b'
#define COUNT_LINES_FLAG       'c'
#define IGNORE_CASE_FLAG       'i'
#define LINE_NUMBER_FLAG       'n'
#define PRINT_NON_MATCH_FLAG   'v'
#define LINE_STRICT_MATCH_FLAG 'x'
#define REGEX_PRESENT_FLAG     'E'

#define ARG_IS_FLAG(arg)      (arg[0] == '-')
#define ARG_GET_FLAG(arg)     (arg[1])

/* private functions*/
unsigned int args_parser_update_flags(arguments_t* arguments, char flag, char const* optionl_value) {
    unsigned int num_args_processed = 1;
    switch (flag) {
        case LINES_AFTER_MATCH_FLAG:
            arguments->num_lines_after_match = atoi(optionl_value);
            num_args_processed++;
            break;
        case LINE_OFFSET_FLAG:
            arguments->print_line_offset = true;
            break;
        case COUNT_LINES_FLAG:
            arguments->print_count_lines = true;
            break;
        case IGNORE_CASE_FLAG:
            arguments->ignore_case = true;
            break;
        case LINE_NUMBER_FLAG:
            arguments->print_line_number = true;
            break;
        case PRINT_NON_MATCH_FLAG:
            arguments->print_non_match = true;
            break;
        case LINE_STRICT_MATCH_FLAG:
            arguments->line_strict_match = true;
            break;
        case REGEX_PRESENT_FLAG:
            arguments->regex_pattern = optionl_value;
            num_args_processed++;
            break;
        default:
            printf("Invalid flag\n");
            num_args_processed = 0;
            break;
    }
    return num_args_processed;
}

/* public functions*/
void parse_arguments(int argc, char const *argv[], arguments_t* arguments) {
    char const* curr_arg = NULL;
    unsigned int args_processed_in_iteration = 0;
    int i = 1;

    for (; i < argc - 1;) {
        curr_arg = argv[i];
        if (ARG_IS_FLAG(curr_arg)) {
            args_processed_in_iteration = args_parser_update_flags(arguments, ARG_GET_FLAG(curr_arg), argv[i+1]);
        } else {
            arguments->search_pattern = curr_arg;
            args_processed_in_iteration = 1;
        }

        if (args_processed_in_iteration == 0) {
            exit(EXIT_FAILURE);
        }
        i += args_processed_in_iteration;
    }

    if (i == argc - 1 && !ARG_IS_FLAG(argv[i])) {
        if (arguments->regex_pattern == NULL && arguments->search_pattern == NULL) {
            arguments->search_pattern = argv[i];
            arguments->input_stream = stdin;
        } else {
            arguments->input_stream = fopen(argv[i], "r");
            if (arguments->input_stream == NULL) {
                printf("failed to open file %s\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        }
    } else {
        arguments->input_stream = stdin;
    }
}

void init_arguments(arguments_t* arguments) {
    memset(arguments, 0x00, sizeof(arguments_t));
}