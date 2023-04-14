#include "args_parser.h"

int main(int argc, char const *argv[])
{
    arguments_t args;
    init_arguments(&args);

    parse_arguments(argc, argv, &args);
    return 0;
}
