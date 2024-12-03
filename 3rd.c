#include "common/files.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    unsigned int acc;
    bool do_flag;
} LineProcessingContext;

const char *is_mul(const char *c, unsigned int *res) {
    if (*c++ != 'm')
        return NULL;
    if (*c++ != 'u')
        return NULL;
    if (*c++ != 'l')
        return NULL;
    if (*c++ != '(')
        return NULL;
    int num_a = 0, num_b = 0;
    while (*c >= '0' && *c <= '9') {
        num_a = num_a * 10;
        num_a += *c - '0';
        c++;
    }
    if (*c++ != ',')
        return NULL;
    while (*c >= '0' && *c <= '9') {
        num_b = num_b * 10;
        num_b += *c - '0';
        c++;
    }
    if (*c++ != ')')
        return NULL;
    *res = num_a * num_b;
    return c;
}

void process_line_callback(const char *line, void *context){
    const char *c = line;
    LineProcessingContext *ctx = (LineProcessingContext *)context;

    while (*c != '\0') {
        unsigned int is_mul_res = 0;
        const char *next = is_mul(c, &is_mul_res);
        if (next) {
            ctx->acc += is_mul_res;
            c = next;
        } else
            c++;
    }
}

int main() {
    const char *filename = "inputs/3rd.txt";

    LineProcessingContext context = {
        .acc = 0,
        .do_flag = true
    };

    process_file_lines(filename, process_line_callback, &context);

    printf("\nACC: %d\n", context.acc);
}
