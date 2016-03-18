#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <limits.h>

struct Settings {
    char command;
    char *argument;

    char dir_root[PATH_MAX + 1];
    char dir_library[PATH_MAX + 1];

    char name[50];
    char replace_files_in_package[50];

    char **argv;
    int argc;
    int argi;
};

void init_settings(struct Settings *settings);
struct Settings parse_arguments(int argc, char *argv[]);
void set_option(const char *name, const char *value, struct Settings *settings);
const char *take_next_argv(struct Settings *settings);
const char *get_option(const char *value, const char *error_message);

#endif
