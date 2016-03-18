#include "../commands.h"
#include "../utils.h"
#include "pkgr/library.h"
#include <stdlib.h>

int query_owner(const char *library, const char *file);

void query(struct Settings *settings) {
    if (strcmp(settings->argument, "installed") == 0) {
        execute("ls %s/", settings->dir_library);
    } else if (strcmp(settings->argument, "owner") == 0) {
        int not_found = 0;

        const char *file;
        while ((file = take_next_argv(settings))) {
            not_found += query_owner(settings->dir_library, file);
        }

        if (not_found)
            EXIT_WITH_ERROR("%d files are not owned", not_found);
    } else {
        EXIT_WITH_ERROR("Unknown query option: %s", settings->argument);
    }
}

// helpers

int query_owner(const char *library, const char *file) {
    char line[LINE_MAX + 1];
    if (library_get_owner(library, file, line)) {
        printf("%s: %s\n", line, file);
        return 0;
    }
    return 1;
}
