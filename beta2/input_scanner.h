#ifndef INPUT_SCANNER_H
#define INPUT_SCANNER_H

#include <stdio.h>
#include "args_parser.h"

typedef struct {
    FILE* input_stream;
    unsigned int current_offset;
} input_scanner_t;

void scan_input(arguments_t* arguments);

#endif