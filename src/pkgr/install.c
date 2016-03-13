#include "install.h"
#include "library.h"
#include "package.h"
#include "../utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define MODE_755 S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH
#define MKDIR_MODE MODE_755

void install(struct Settings *settings) {
    const char *found = strrchr(settings->argument, '/');
    int offset = found - settings->argument + 1;
    int length = strlen(settings->argument) - offset;

    char name[50];
    strncpy(name, settings->argument + offset, length - 7);
    name[length - 7] = 0;

    char package_dir[PATH_MAX + 1];
    sprintf(package_dir, "%s/%s", settings->dir_library, name);

    mkdir(package_dir, MKDIR_MODE);

    char owned[PATH_MAX + 1];
    sprintf(owned, "%s/owns", package_dir);
    FILE *fowned = fopen(owned, "w");

    FILE *flist = package_read_file_list(settings->argument);
    char file[LINE_MAX + 1];
    char current_owner[1000];
    int already_owned = 0;
    while (read_trimmed_line(flist, file)) {
        if (library_get_owner(settings->dir_library, file, current_owner)) {
            fprintf(stderr, "%s is currently owned by %s\n", file, current_owner);
            already_owned++;
        }

        fprintf(fowned, "%s\n", file);
    }
    fclose(flist);

    fclose(fowned);

    if (already_owned) {
        fprintf(stderr, "%d files are already owned by other packages\n", already_owned);
        exit(EXIT_FAILURE);
    }

    package_extract_files(settings->argument, settings->dir_root);
}
