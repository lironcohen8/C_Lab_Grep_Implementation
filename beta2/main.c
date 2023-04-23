#include "args_parser.h"
#include "input_scanner.h"

int main(int argc, char const *argv[])
{
    arguments_t args;
    parse_arguments(argc, argv, &args);
    scan_input(&args);
    free_args_internals(&args);
    return 0;
}
