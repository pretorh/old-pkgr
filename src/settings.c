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

    static const char short_options[] = "";
    static struct option long_options[] = {
        {0, 0, 0, 0}
    };
    int c, index;

    while ((c = getopt_long (argc, argv, short_options, long_options, &index)) != -1) {
        switch (c) {
            case 0:
                // long options
                if (long_options[index].flag != 0)
                    break;
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
