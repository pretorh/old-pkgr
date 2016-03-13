#include "../utils.h"
#include <stdlib.h>

void execute_command(const char *command) {
    printf("$> %s\n", command);
    system(command);
}

FILE *execute_for_reading(const char *command) {
    printf("$>%s\n", command);
    FILE *f = popen(command, "r");
    if (f == NULL) {
        perror("Error opening pipe");
        exit(EXIT_FAILURE);
    }
    return f;
}
