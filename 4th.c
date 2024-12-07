#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "common/files.h"

typedef struct {
    unsigned int acc;
} LineProcessingContext;

uint8_t index_score[500];
uint8_t index_score_reverse[500];

void process_lines_horizontally(const char *line, void *context){
    const char *c = line;
    LineProcessingContext *ctx = (LineProcessingContext *)context;

    do {
        if (*c != 'X') continue;
        if (*(c+1) != 'M') continue;
        if (*(c+2) != 'A') continue;
        if (*(c+3) != 'S') continue;
        ctx->acc++;
        printf("XMAS Horizontal!\n");
    } while (*c++ != '\0');

    c -= 2;

    do {
        if (*c != 'X') continue;
        if (*(c-1) != 'M') continue;
        if (*(c-2) != 'A') continue;
        if (*(c-3) != 'S') continue;
        ctx->acc++;
        printf("XMAS Horizontal Reverted!\n");
    } while (*c-- != '\0');
}

void process_lines_vertically(const char *line, void *context){
    const char *c = line;
    uint8_t *score = index_score;
    uint8_t *score_reverse = index_score_reverse;
    LineProcessingContext *ctx = (LineProcessingContext *)context;

    while (*c != '\n') {
        uint8_t prev = *score;
        if (*score < 1  && *c == 'X') (*score)++;
        if (*score == 1 && *c == 'M') (*score)++;
        if (*score == 2 && *c == 'A') (*score)++;
        if (*score == 3 && *c == 'S') {
            ctx->acc++;
            *score = 0;
            printf("XMAS Vertical!\n");
        };
        if (prev == *score) *score = 0;

        prev = *score_reverse;
        if (*score_reverse < 1  && *c == 'S') (*score_reverse)++;
        if (*score_reverse == 1 && *c == 'A') (*score_reverse)++;
        if (*score_reverse == 2 && *c == 'M') (*score_reverse)++;
        if (*score_reverse == 3 && *c == 'X') {
            ctx->acc++;
            *score_reverse = 0;
            printf("XMAS Vertical Reverted!\n");
        };
        if (prev == *score_reverse) *score_reverse = 0;

        c++;
        score++;
        score_reverse++;
    }

}

int main() {
    const char *filename = "inputs/ex-4th.txt";

    LineProcessingContext context = {
        .acc = 0
    };

    process_file_lines(filename, process_lines_horizontally, &context);

    for (int i = 0; i < 500; i++) {
        index_score[i] = 0;
        index_score_reverse[i] = 0;
    }
    
    process_file_lines(filename, process_lines_vertically, &context);

    printf("\nACC: %d\n", context.acc);
}
