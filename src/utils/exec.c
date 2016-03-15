#include "../utils.h"
#include <stdlib.h>

void execute_command(const char *command) {
    LOG_COMMAND(command);
    system(command);
}

FILE *execute_for_reading(const char *command) {
    LOG_COMMAND(command);
    FILE *f = popen(command, "r");
    if (f == NULL) {
        perror("Error opening pipe");
        exit(EXIT_FAILURE);
    }
    return f;
}
