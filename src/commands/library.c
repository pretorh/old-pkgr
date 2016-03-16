#include "../commands.h"
#include "../pkgr/library.h"
#include <stdlib.h>
#include "../utils.h"

void library(struct Settings *settings) {
    if (strcmp(settings->argument, "remove-ownership") == 0) {
        const char *package = get_option(settings->name, "--name <package-name> must be specified");

        const char *file;
        while ((file = take_next_argv(settings))) {
            library_remove_ownership(settings->dir_library, package, file);
        }
    } else {
        EXIT_WITH_ERROR("Unknown library option: %s", settings->argument);
    }
}
