#include "args_parser.h"
#include "string_utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES_AFTER_MATCH_FLAG 'A'
#define LINE_OFFSET_FLAG 'b'
#define COUNT_LINES_FLAG 'c'
#define IGNORE_CASE_FLAG 'i'
#define LINE_NUMBER_FLAG 'n'
#define PRINT_NON_MATCH_FLAG 'v'
#define LINE_STRICT_MATCH_FLAG 'x'
#define REGEX_PRESENT_FLAG 'E'

#define ARG_IS_FLAG(arg) (arg[0] == '-')
#define ARG_GET_FLAG(arg) (arg[1])

#define INIT_VALUE_FOR_MEMSET 0x00

/* private functions */
unsigned int update_args_flags(arguments_t* arguments, char flag, char const* optionl_value)
{
  unsigned int num_args_processed = 1;
  switch (flag) {
    case LINES_AFTER_MATCH_FLAG:
      arguments->num_lines_after_match = atoi(optionl_value);
      arguments->separator_required = true;
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
      alloc_str_and_copy(&arguments->search_pattern, optionl_value);
      num_args_processed++;
      break;
    default:
      printf("Invalid flag\n");
      num_args_processed = 0;
      break;
  }
  return num_args_processed;
}

int process_arg(char const* curr_arg, char const* optional_value, arguments_t* arguments)
{
  if (ARG_IS_FLAG(curr_arg)) {
    return update_args_flags(arguments, ARG_GET_FLAG(curr_arg), optional_value);
  } else {
    alloc_str_and_copy(&arguments->search_pattern, curr_arg);
    return 1;
  }
}

void process_last_arg(char const* last_arg, arguments_t* arguments)
{
  if (ARG_IS_FLAG(last_arg)) {
    process_arg(last_arg, NULL, arguments);
  } else {
    if (arguments->search_pattern == NULL) {
      alloc_str_and_copy(&arguments->search_pattern, last_arg);
    } else {
      arguments->input_filename = last_arg;
    }
  }
}

/* public functions */
void parse_arguments(int argc, char const* argv[], arguments_t* arguments)
{
  memset(arguments, INIT_VALUE_FOR_MEMSET, sizeof(arguments_t));
  char const *curr_arg = NULL, *optional_val = NULL;
  unsigned int count_args_processed_in_iteration = 0;
  int argv_index = 1;

  for (; argv_index < argc - 1;) {
    curr_arg = argv[argv_index];
    optional_val = argv[argv_index + 1];
    count_args_processed_in_iteration = process_arg(curr_arg, optional_val, arguments);
    assert(count_args_processed_in_iteration != 0);
    argv_index += count_args_processed_in_iteration;
  }
  if (argv_index == argc - 1) {
    process_last_arg(argv[argv_index], arguments);
  }
  assert(arguments->search_pattern != NULL);
  if (arguments->ignore_case) {
    lowercase_string(arguments->search_pattern, arguments->search_pattern);
  }
}

void free_args_internals(arguments_t* arguments)
{
  if (arguments->search_pattern != NULL) {
    free(arguments->search_pattern);
  }
}