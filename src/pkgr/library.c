#include "library.h"
#include "../utils.h"
#include <limits.h>

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
