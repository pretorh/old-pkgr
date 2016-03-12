#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <limits.h>

struct Settings {
    char command;
    char *argument;

    char **argv;
    int argc;
    int argi;
};

void init_settings(struct Settings *settings);
struct Settings parse_arguments(int argc, char *argv[]);

#endif
