#ifndef _PKGR_PACKAGE_H_
#define _PKGR_PACKAGE_H_

#include <stdio.h>

#define DIR_ROOT "files"

void package_create(const char *root, const char *name);
FILE *package_read_file_list(const char *archive);
void package_extract_files(const char *archive, const char *to);
const char *package_get_name(const char *archive, char *name);

#endif
