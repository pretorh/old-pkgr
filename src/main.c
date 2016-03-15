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

        case 'Q':
            query(&settings);
            break;

        default:
            EXIT_WITH_ERROR("No command given\nValid commands: %s",
                "P: package\n"
                "I: install\n"
                "Q: query\n");
    }

    return 0;
}
