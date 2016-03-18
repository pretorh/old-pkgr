#include "../commands.h"
#include "../pkgr/install.h"

void install(struct Settings *settings) {
    install_package(settings->dir_library,
        settings->dir_root,
        settings->argument,
        settings->replace_files_in_package);
}
