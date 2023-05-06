#include "regex_handler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    // TEST PROGRAM DELETE ONCE DONE !!!!
    // TEST PROGRAM DELETE ONCE DONE !!!!
    // argv[1] is string
    // argv[2] is pattern
    // argv[3] is strict
    regex_t regex;
    bool strict = atoi(argv[3]);
    compile_regex(argv[2], strlen(argv[2]), &regex);
    printf("%u\n", is_regex_match_in_line(argv[1], strlen(argv[1]), &regex, strict));
    return 0;
}