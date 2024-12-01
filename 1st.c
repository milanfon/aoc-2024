#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define DELIMITER "   "
#define VARIANT_B

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

int find_the_smallest_number_but_higher(int *arr, int size, int higher_than){
    int *smallest = NULL;
    int *val = arr;
    for (int i = 0; i < size; i++) {
        if (*val >= higher_than && (smallest == NULL || *val < *smallest))
            smallest = val;
        val++;
    }
    int ret = *smallest;
    *smallest = 0;
    return ret;
}

int find_num_count_in_array(int *arr, int size, int number){
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == number)
            count++;
    }
    return count;
}

int main() {
    const char *filename = "inputs/1st.txt";

    int line_count = count_lines_in_file(filename);
    printf("Line count: %d\n", line_count);

    int a_arr[line_count];
    int b_arr[line_count];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error openning file!");
        return EXIT_FAILURE;
    }

    char buffer[MAX_LINE_LENGTH];

    int iter = 0;
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        char *token = strtok(buffer, DELIMITER);
        a_arr[iter] = atoi(token);
        token = strtok(NULL, DELIMITER);
        b_arr[iter] = atoi(token);
        iter++;
    }

    if (ferror(file))
        perror("Error reading file");

    fclose(file);

#ifdef VARIANT_A
    int a_smallest = 0;
    int b_smallest = 0;
    int acc = 0;
    for (int i = 0; i < line_count; i++) {
        a_smallest = find_the_smallest_number_but_higher(a_arr, line_count, a_smallest);
        b_smallest = find_the_smallest_number_but_higher(b_arr, line_count, b_smallest);
        int diff = abs(a_smallest - b_smallest);
        // printf("A: %d\nB: %d\n", a_smallest, b_smallest);
        // printf("Diff: %d\n", diff);
        acc += diff;
    }
    
    printf("Acc: %d\n", acc);
#endif


#ifdef VARIANT_B
    int *num = a_arr;
    int acc = 0;
    for (int i = 0; i < line_count; i++) {
        int count = find_num_count_in_array(b_arr, line_count, *num);
        acc += *num * count;
        num++;
    }
    
    printf("Acc: %d\n", acc);
#endif

    return EXIT_SUCCESS;
}
