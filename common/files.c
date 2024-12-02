#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int count_lines_in_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int line_count = 0;
    char buffer[MAX_LINE_LENGTH];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
        line_count++;

    if (ferror(file)) {
        perror("Error reading file");
        fclose(file);
        return -1;
    }

    fclose(file);
    return line_count;
}

void process_file_lines(const char *filename, void (*process_line)(const char *, void *), void *context) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        process_line(buffer, context);
    }

    if (ferror(file))
        perror("Error reading file");

    fclose(file);
}

