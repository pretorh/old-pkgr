#include "package.h"
#include "../utils.h"

void package(struct Settings *settings) {
    const char *root = settings->argument;
    char archive[PATH_MAX + 1];
    sprintf(archive, "%s/%s.tar.xz",
        root,
        settings->name[0] == 0 ? "package" : settings->name);

    execute("tar cpPJf %s --transform 's,%s/,,' --owner=0 --group=0 %s/"DIR_ROOT,
            archive, root, root);
}

void package_dump_file_list(const char *archive, const char *to) {
    execute("tar tPf %s --wildcards "DIR_ROOT"/* "
            "--transform 's,"DIR_ROOT",,' "
            "--show-stored-names | grep -v '/$' > %s",
            archive, to);
}

void package_extract_files(const char *archive, const char *to) {
    execute("tar vxPf %s --wildcards "DIR_ROOT"/* --transform 's,"DIR_ROOT",%s,' --show-stored-names",
        archive, to);
}
