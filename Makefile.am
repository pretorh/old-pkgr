bin_PROGRAMS = pkgr
EXTRA_DIST = $(TESTS)

TESTS =
TESTS += tests/package/create-tarxz.sh
TESTS += tests/package/create-with-name.sh
TESTS += tests/install/added-to-library.sh
TESTS += tests/install/files-owned.sh
TESTS += tests/spec/install_create-files.sh
TESTS += tests/spec/install_blocked-if-file-already-owned.sh
TESTS += tests/spec/install_replace-file-ownership.sh
XFAIL_TESTS =
XFAIL_TESTS += tests/spec/install_replace-file-ownership.sh

pkgr_CFLAGS = -ggdb -pedantic -Wall -Wextra
pkgr_SOURCES = src/main.c
pkgr_SOURCES += src/settings.c
pkgr_SOURCES += src/commands/install.c
pkgr_SOURCES += src/commands/package.c
pkgr_SOURCES += src/commands/query.c
pkgr_SOURCES += src/utils/exec.c
pkgr_SOURCES += src/utils/functions.c
pkgr_SOURCES += src/utils/io.c
pkgr_SOURCES += src/pkgr/install.c
pkgr_SOURCES += src/pkgr/library.c
pkgr_SOURCES += src/pkgr/package.c
