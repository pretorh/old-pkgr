#ifndef _PKGR_PACKAGE_H_
#define _PKGR_PACKAGE_H_

#include "settings.h"
#include <stdio.h>

#define DIR_ROOT "files"

void package(struct Settings *settings);
FILE *package_read_file_list(const char *archive);
void package_extract_files(const char *archive, const char *to);

#endif
