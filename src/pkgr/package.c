#include "package.h"
#include "../utils.h"

void package(struct Settings *settings) {
    const char *root = settings->argument;
    char archive[PATH_MAX + 1];
    sprintf(archive, "%s/package.tar.xz", root);

    execute("tar cpPJf %s --transform 's,%s/,,' --owner=0 --group=0 %s/"DIR_ROOT,
            archive, root, root);
}
