#include "install.h"
#include "package.h"

void install(struct Settings *settings) {
    package_extract_files(settings->argument, settings->dir_root);
}
