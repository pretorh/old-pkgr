#include "../commands.h"
#include "../utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void query(struct Settings *settings) {
    if (strcmp(settings->argument, "installed") == 0) {
        execute("ls %s/", settings->dir_library);
    } else {
        fprintf(stderr, "Unknown query option: %s\n", settings->argument);
        exit(EXIT_FAILURE);
    }
}
