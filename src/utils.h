#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>

#define execute(f, ...) {\
        char command[1000]; \
        sprintf(command, f, __VA_ARGS__); \
        execute_command(command); \
    }
#define start_pipe(pipe_name, f, ...) \
    char command[1000]; \
    sprintf(command, f, __VA_ARGS__); \
    pipe_name = execute_for_reading(command);

void execute_command(const char *command);
FILE *execute_for_reading(const char *command);

#endif
