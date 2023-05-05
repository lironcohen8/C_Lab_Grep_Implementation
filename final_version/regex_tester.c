#include "regex_handler.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // TEST PROGRAM DELETE ONCE DONE !!!!
    // TEST PROGRAM DELETE ONCE DONE !!!!
    // argv[1] is string
    // argv[2] is pattern
    regex_t regex;
    compile_regex(argv[2], &regex);
    printf("%u\n", is_regex_match_in_line(argv[1], strlen(argv[1]), &regex, false));
    return 0;
}