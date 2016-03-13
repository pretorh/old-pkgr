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

void validate_files_in_package(const char *library, const char *archive, const char *owned);

void install(struct Settings *settings) {
    char name[50], package_dir[PATH_MAX + 1], owned[PATH_MAX + 1];
    package_get_name(settings->argument, name);
    library_get_package_dir(settings->dir_library, name, package_dir);
    library_get_package_owns_file(settings->dir_library, name, owned);

    mkdir(package_dir, MKDIR_MODE);

    validate_files_in_package(settings->dir_library, settings->argument, owned);

    package_extract_files(settings->argument, settings->dir_root);
}

void validate_files_in_package(const char *library, const char *archive, const char *owned) {
    FILE *fowned = fopen(owned, "w");

    FILE *flist = package_read_file_list(archive);
    char file[LINE_MAX + 1];
    char current_owner[1000];
    int already_owned = 0;
    while (read_trimmed_line(flist, file)) {
        if (library_get_owner(library, file, current_owner)) {
            fprintf(stderr, "%s is currently owned by %s\n", file, current_owner);
            already_owned++;
        } else {
            fprintf(fowned, "%s\n", file);
        }
    }
    fclose(flist);

    fclose(fowned);

    if (already_owned) {
        fprintf(stderr, "%d files are already owned by other packages\n", already_owned);
        exit(EXIT_FAILURE);
    }
}
