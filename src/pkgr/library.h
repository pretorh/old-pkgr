#ifndef _PKGR_LIBRARY_H_
#define _PKGR_LIBRARY_H_

const char *library_get_owner(const char *library, const char *file, char *owner);
const char *library_get_package_dir(const char *library, const char *package_name, char *package_dir);
const char *library_get_package_owns_file(const char *library, const char *package_name, char *package_file);

#endif
