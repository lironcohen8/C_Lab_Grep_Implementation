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

    char const * pattern = argv[PATTERN_ARG_NUM];
    FILE* file = fopen(argv[FILE_ARG_NUM], "r");

    if (file == NULL) {
        printf("Error opening file %s\n", argv[FILE_ARG_NUM]);
        exit(EXIT_FAILURE);
    }

    char* line_buffer = NULL;
    size_t len = 0;

    while ((getline(&line_buffer, &len, file)) != -1) {
        if (strstr(line_buffer, pattern) != NULL) {
            printf("%s", line_buffer);
        }
    }

    fclose(file);
    if (line_buffer != NULL) {
        free(line_buffer);
    }

    return 0;
}
