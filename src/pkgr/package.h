#ifndef _PKGR_PACKAGE_H_
#define _PKGR_PACKAGE_H_

#include "settings.h"

#define DIR_ROOT "files"

void package(struct Settings *settings);
void package_extract_files(const char *archive, const char *to);

#endif
