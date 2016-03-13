#include "package.h"
#include "../utils.h"
#include <limits.h>

void package_create(const char *root, const char *name) {
    char archive[PATH_MAX + 1];
    sprintf(archive, "%s/%s.tar.xz", root, name);

    execute("tar cpPJf %s --transform 's,%s/,,' --owner=0 --group=0 %s/"DIR_ROOT,
            archive, root, root);
}

FILE *package_read_file_list(const char *archive) {
    FILE *f;
    start_pipe(f, "tar tPf %s --wildcards "DIR_ROOT"/* "
            "--transform 's,"DIR_ROOT",,' "
            "--show-stored-names | grep -v '/$'",
            archive);
    return f;
}

void package_extract_files(const char *archive, const char *to) {
    execute("tar vxPf %s --wildcards "DIR_ROOT"/* --transform 's,"DIR_ROOT",%s,' --show-stored-names",
        archive, to);
}

const char *package_get_name(const char *archive, char *name) {
    split_filename(archive, NULL, name);
    name[strlen(name) - 7] = 0;         // drop .tar.xz
    return name;
}
