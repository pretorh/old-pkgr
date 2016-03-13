#include "../commands.h"
#include "../utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TRIM_NEWLINE(s) \
    if (strlen(s) && s[strlen(s) - 1] == '\n') \
        s[strlen(s) - 1] = 0;

void query_owner(const char *library, const char *file);

void query(struct Settings *settings) {
    if (strcmp(settings->argument, "installed") == 0) {
        execute("ls %s/", settings->dir_library);
    } else if (strcmp(settings->argument, "owner") == 0) {
        const char *file;
        while ((file = take_next_argv(settings))) {
            query_owner(settings->dir_library, file);
        }
    } else {
        fprintf(stderr, "Unknown query option: %s\n", settings->argument);
        exit(EXIT_FAILURE);
    }
}

void query_owner(const char *library, const char *file) {
    FILE *f;
    start_pipe(f, "basename $(dirname `grep -l %s %s/**/owns`)", file, library);

    char line[LINE_MAX + 1];
    if (fgets(line, LINE_MAX, f)) {
        TRIM_NEWLINE(line);
        printf("%s: %s\n", line, file);
    }

    fclose(f);
}
