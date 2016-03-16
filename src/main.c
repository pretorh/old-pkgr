#include "settings.h"
#include "commands.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct Settings settings = parse_arguments(argc, argv);

    switch (settings.command) {
        case 'P':
            package(&settings);
            break;

        case 'I':
            install(&settings);
            break;

        case 'L':
            library(&settings);
            break;

        case 'Q':
            query(&settings);
            break;

        default:
            EXIT_WITH_ERROR("No command given. Valid commands: %s",
                "\nP: package"
                "\nI: install"
                "\nL: library"
                "\nQ: query");
    }

    return 0;
}
