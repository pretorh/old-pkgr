bin_PROGRAMS = pkgr
EXTRA_DIST = $(TESTS)

TESTS =
XFAIL_TESTS =
TESTS += tests/spec/install_create-files.sh
XFAIL_TESTS += tests/spec/install_create-files.sh

pkgr_CFLAGS = -ggdb -pedantic -Wall -Wextra
pkgr_SOURCES = src/main.c
pkgr_SOURCES += src/settings.c
