#include "install.h"
#include "package.h"
#include <string.h>
#include <stdio.h>
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
    package_dump_file_list(settings->argument, owned);

    package_extract_files(settings->argument, settings->dir_root);
}
