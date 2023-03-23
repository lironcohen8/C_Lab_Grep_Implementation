#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("Wrong number of arguments\n");
        exit(EXIT_FAILURE);
    }

    char const * pattern = argv[1];
    FILE* file = fopen(argv[2], "r");

    if (file == NULL) {
        printf("Error opening file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    char* line_buffer = NULL;
    size_t len = 0;
    ssize_t chars_read_in_line = 0;

    while ((chars_read_in_line = getline(&line_buffer, &len, file)) != -1) {
        if (strstr(line_buffer, pattern) != NULL) {
            printf("%s", line_buffer);
        }
    }

    fclose(file);
    if (line_buffer) {
        free(line_buffer);
    }

    return 0;
}
