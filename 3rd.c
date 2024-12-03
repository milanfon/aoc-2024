#include "common/files.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    unsigned int acc;
} LineProcessingContext;

void process_line_callback(const char *line, void *context){
    const char *c = line;
    LineProcessingContext *ctx = (LineProcessingContext *)context;

    while (*c != '\0') {
        if (*c++ != 'm')
            continue;
        if (*c++ != 'u')
            continue;
        if (*c++ != 'l')
            continue;
        if (*c++ != '(')
            continue;
        int num_a = 0, num_b = 0;
        while (*c >= '0' && *c <= '9') {
            num_a = num_a * 10;
            num_a += *c - '0';
            c++;
        }
        if (*c++ != ',')
            continue;
        while (*c >= '0' && *c <= '9') {
            num_b = num_b * 10;
            num_b += *c - '0';
            c++;
        }
        if (*c++ != ')')
            continue;
        //printf("\n\nMUL(%d,%d)\n", num_a, num_b);
        ctx->acc += num_a * num_b;
    }
}

int main() {
    const char *filename = "inputs/3rd.txt";

    LineProcessingContext context = {
        .acc = 0
    };

    process_file_lines(filename, process_line_callback, &context);

    printf("\nACC: %d\n", context.acc);
}
