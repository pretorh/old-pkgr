#include "settings.h"
#include <string.h>
#include <getopt.h>
#include <stdlib.h>

void init_settings(struct Settings *settings) {
    memset(settings, 0, sizeof(*settings));
}

struct Settings parse_arguments(int argc, char *argv[]) {
    struct Settings res;
    init_settings(&res);

    static const char short_options[] = "I:P:";
    static struct option long_options[] = {
        {"install", required_argument, 0, 'I'},
        {"pack", required_argument, 0, 'P'},
        {0, 0, 0, 0}
    };
    int c, index;

    while ((c = getopt_long (argc, argv, short_options, long_options, &index)) != -1) {
        switch (c) {
            case 'I':
            case 'P':
                res.command = c;
                res.argument = optarg;
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
