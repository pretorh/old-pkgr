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

#define LOG_COMMAND(command) \
    printf("$> %s\n", command);

#define EXIT_WITH_ERROR(f, ...) { \
        fprintf(stderr, f"\n", __VA_ARGS__); \
        exit(EXIT_FAILURE); \
    }
#define EXIT_SUB_PROCESS_ERROR(command, issue, code) {\
        fprintf(stderr, "Error: Sub process failed\n" \
        "\tcommand: %s\n" \
        "\t%s (%d)\n", \
        command, issue, code); \
        exit(EXIT_FAILURE); \
    }

typedef int LineCallback(const char *line, void *data);

// exec
void execute_command(const char *command);
FILE *execute_for_reading(const char *command);
int close_pipe(FILE *f, int allow_non_zero_exit);
int get_exit_code(const char *command, int status);
void assert_success_exit(const char *command, int status);

// io
const char *read_trimmed_line(FILE *f, char *into);
void for_each_line(FILE *f, void *data, LineCallback *callback);

// functions
int split_filename(const char *from, char *dir, char *file);

#endif
