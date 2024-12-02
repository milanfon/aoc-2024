#ifndef FILES_H
#define FILES_H

int count_lines_in_file(const char *filename);

void process_file_lines(const char *filename, void (*process_line)(const char *, void *), void *context);

#endif
