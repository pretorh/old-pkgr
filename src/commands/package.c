#include "../commands.h"
#include "../pkgr/package.h"

void package(struct Settings *settings) {
    const char *root = settings->argument;
    const char *name = settings->name[0] == 0 ? "package" : settings->name;
    package_create(root, name);
}
