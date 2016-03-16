#include "library.h"
#include "../utils.h"
#include <limits.h>
#include <stdlib.h>

#define FILE_OWNS "owns"

const char *library_get_owner(const char *library, const char *file, char *owner) {
    FILE *f;
    start_pipe(f, "grep -l ^%s$ %s/**/"FILE_OWNS, file, library);

    char line[LINE_MAX + 1];
    const char *result = NULL;
    if ((result = read_trimmed_line(f, line))) {
        // the base of the dir of the file (file -> dir -> parent dir)
        char dir[PATH_MAX + 1];
        split_filename(line, dir, NULL);
        split_filename(dir, NULL, owner);
    }

    fclose(f);
    return result;
}

const char *library_get_package_dir(const char *library, const char *package_name, char *package_dir) {
    sprintf(package_dir, "%s/%s", library, package_name);
    return package_dir;
}

const char *library_get_package_owns_file(const char *library, const char *package_name, char *package_file) {
    char package_dir[PATH_MAX + 1];
    library_get_package_dir(library, package_name, package_dir);
    sprintf(package_file, "%s/"FILE_OWNS, package_dir);
    return package_file;
}

void library_remove_ownership(const char *library_dir, const char *package_name, const char *package_file) {
    char current_owner[50];
    if (library_get_owner(library_dir, package_file, current_owner) == 0)
        EXIT_WITH_ERROR("File %s is not owned by any package", package_file);
    if (strcmp(package_name, current_owner))
        EXIT_WITH_ERROR("File %s is not owned by %s (but by %s)", package_file, package_name, current_owner);

    execute("sed --in-place '\\:^%s$:d' %s/%s/"FILE_OWNS,
        package_file, library_dir, package_name);
}
