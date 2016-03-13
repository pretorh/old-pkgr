#include "settings.h"
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

void init_settings(struct Settings *settings) {
    memset(settings, 0, sizeof(*settings));
}

struct Settings parse_arguments(int argc, char *argv[]) {
    struct Settings res;
    init_settings(&res);

    static const char short_options[] = "I:P:Q:";
    static struct option long_options[] = {
        // commands
        {"install", required_argument, 0, 'I'},
        {"pack", required_argument, 0, 'P'},
        {"query", required_argument, 0, 'Q'},
        // options
        {"root-dir", required_argument, 0, 0},
        {"library-dir", required_argument, 0, 0},
        {"name", required_argument, 0, 0},
        {0, 0, 0, 0}
    };
    int c, index;

    while ((c = getopt_long (argc, argv, short_options, long_options, &index)) != -1) {
        switch (c) {
            case 'I':
            case 'P':
            case 'Q':
                res.command = c;
                res.argument = optarg;
                break;

            case 0:
                if (long_options[index].flag != 0)
                    break; // flag set
                set_option(long_options[index].name, optarg, &res);
                break;

            case '?':
            default:
                exit(EXIT_FAILURE);
        }
    }

    res.argv = argv + optind;
    res.argc = argc - optind;
    res.argi = 0;
    return res;
}

void set_option(const char *name, const char *value, struct Settings *settings) {
    char *to_dir = 0;
    char *to_option = 0;

    if (strcmp(name, "root-dir") == 0) {
        to_dir = settings->dir_root;
    } else if (strcmp(name, "library-dir") == 0) {
        to_dir = settings->dir_library;
    } else if (strcmp(name, "name") == 0) {
        to_option = settings->name;
    } else {
        fprintf(stderr, "unknown setting %s\n", name);
        exit(1);
    }

    if (to_dir)
        strcpy(to_dir, value);
    if (to_option)
        strcpy(to_option, value);
}

const char *take_next_argv(struct Settings *settings) {
    if (settings->argi >= settings->argc)
        return NULL;
    return settings->argv[settings->argi++];
}
