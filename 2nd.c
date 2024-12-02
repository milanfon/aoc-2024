#include "common/files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DELIMITER " "

typedef struct {
    int acc;
} LineProcessingContext;

void process_line_callback(const char *line, void *context) {
    char line_copy[1024];
    strncpy(line_copy, line, 1024 - 1);
    LineProcessingContext *ctx = (LineProcessingContext *)context;
    char *token = strtok((char *)line, DELIMITER);
    int num = atoi(token);
    bool increasing = true;
    token = strtok(NULL, DELIMITER);
    int next_num = atoi(token);

    if (abs(num - next_num) > 3)
        return;

    if (next_num > num)
        increasing = true;
    else if (next_num < num)
        increasing = false;
    else
        return;

    num = next_num;

    while ((token = strtok(NULL, DELIMITER)) != NULL) {
        next_num = atoi(token);
        if ((increasing && (next_num > num)) || (!increasing && (next_num < num))) {
            int diff = abs(num - next_num);
            if (diff > 3)
                return;
            num = next_num;
        } else
            return;
    }
    printf("Success: %s\n", line_copy);
    ctx->acc++;
}

int main() {
    const char *filename = "inputs/2nd.txt";

    LineProcessingContext context = {
        .acc = 0
    };

    process_file_lines(filename, process_line_callback, &context);
    printf("Acc: %d\n", context.acc);

    return EXIT_SUCCESS;
}
