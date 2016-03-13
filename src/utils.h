#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <string.h>

#define execute(f, ...) {\
        char command[1000]; \
        sprintf(command, f, __VA_ARGS__); \
        execute_command(command); \
    }
#define start_pipe(pipe_name, f, ...) \
    char command[1000]; \
    sprintf(command, f, __VA_ARGS__); \
    pipe_name = execute_for_reading(command);

#define TRIM_NEWLINE(s) \
    if (strlen(s) && s[strlen(s) - 1] == '\n') \
        s[strlen(s) - 1] = 0;

// exec
void execute_command(const char *command);
FILE *execute_for_reading(const char *command);

// io
const char *read_trimmed_line(FILE *f, char *into);

// functions
int split_filename(const char *from, char *dir, char *file);

#endif
