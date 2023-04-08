#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXPECTED_NUM_OF_ARGS 3
#define PATTERN_ARG_NUM 1
#define FILE_ARG_NUM 2

int main(int argc, char const *argv[])
{
    if (argc != EXPECTED_NUM_OF_ARGS) {
        printf("Wrong number of arguments\n");
        exit(EXIT_FAILURE);
    }

    char const * search_pattern = argv[PATTERN_ARG_NUM];
    FILE* input_file = fopen(argv[FILE_ARG_NUM], "r");

    if (input_file == NULL) {
        printf("Error opening file %s\n", argv[FILE_ARG_NUM]);
        exit(EXIT_FAILURE);
    }

    char* line_buffer = NULL;
    size_t len = 0;

    while ((getline(&line_buffer, &len, input_file)) != -1) {
        if (strstr(line_buffer, search_pattern) != NULL) {
            printf("%s", line_buffer);
        }
    }

    fclose(input_file);
    if (line_buffer != NULL) {
        free(line_buffer);
    }

    return 0;
}
