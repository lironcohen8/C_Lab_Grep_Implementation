#include "args_parser.h"
#include "input_scanner.h"

int main(int argc, char const *argv[])
{
  arguments_t args;
  input_scanner_t input_scanner;

  parse_arguments(argc, argv, &args);
  init_input_scanner(&input_scanner, &args);

  scan_input(&input_scanner, &args);

  free_input_scanner_internals(&input_scanner);
  free_args_internals(&args);
  return 0;
}
