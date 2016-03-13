#include "../commands.h"
#include "../utils.h"
#include "pkgr/library.h"
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
    char line[LINE_MAX + 1];
    if (library_get_owner(library, file, line)) {
        printf("%s: %s\n", line, file);
    }
}
