#include "settings.h"
#include "pkgr/package.h"
#include "pkgr/install.h"
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

        default:
            fprintf(stderr, "No command given\n");
            exit(EXIT_FAILURE);
    }

    return 0;
}
