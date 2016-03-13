#include "../commands.h"
#include "../utils.h"
#include <stdlib.h>

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
    if (read_trimmed_line(f, line)) {
        printf("%s: %s\n", line, file);
    }

    fclose(f);
}
