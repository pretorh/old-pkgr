#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>

#define execute(f, ...) {\
        char command[1000]; \
        sprintf(command, f, __VA_ARGS__); \
        execute_command(command); \
    }

void execute_command(const char *command);

#endif
