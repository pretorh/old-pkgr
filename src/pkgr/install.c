#include "install.h"
#include "library.h"
#include "package.h"
#include "../utils.h"
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define MODE_755 S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH
#define MKDIR_MODE MODE_755

struct ValidateData {
    const char *library;
    FILE *fowned;
    int already_owned;
};

void validate_files_in_package(const char *library, const char *archive, const char *owned);
int validate_file_in_package(const char *file, void *data);

void install_package(const char *library, const char *root, const char *archive) {
    char name[50], package_dir[PATH_MAX + 1], owned[PATH_MAX + 1];
    package_get_name(archive, name);
    library_get_package_dir(library, name, package_dir);
    library_get_package_owns_file(library, name, owned);

    mkdir(package_dir, MKDIR_MODE);

    validate_files_in_package(library, archive, owned);

    package_extract_files(archive, root);
}

void validate_files_in_package(const char *library, const char *archive, const char *owned) {
    FILE *fowned = fopen(owned, "w");

    struct ValidateData validate = { library, fowned, 0 };
    FILE *flist = package_read_file_list(archive);
    for_each_line(flist, &validate, &validate_file_in_package);
    fclose(flist);

    fclose(fowned);

    if (validate.already_owned)
        EXIT_WITH_ERROR("%d files are already owned by other packages", validate.already_owned);
}

int validate_file_in_package(const char *file, void *data) {
    struct ValidateData *validate = (struct ValidateData*) data;
    char current_owner[1000];

    if (library_get_owner(validate->library, file, current_owner)) {
        fprintf(stderr, "%s is currently owned by %s\n", file, current_owner);
        validate->already_owned++;
    } else {
        fprintf(validate->fowned, "%s\n", file);
    }

    return 0;
}
