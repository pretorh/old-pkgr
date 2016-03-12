bin_PROGRAMS = pkgr
EXTRA_DIST = $(TESTS)

TESTS =
TESTS += tests/package/create-tarxz.sh
TESTS += tests/spec/install_create-files.sh
XFAIL_TESTS =
XFAIL_TESTS += tests/spec/install_create-files.sh

pkgr_CFLAGS = -ggdb -pedantic -Wall -Wextra
pkgr_SOURCES = src/main.c
pkgr_SOURCES += src/settings.c
pkgr_SOURCES += src/utils/exec.c
pkgr_SOURCES += src/pkgr/package.c
