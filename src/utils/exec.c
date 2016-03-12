#include "../utils.h"
#include <stdlib.h>

void execute_command(const char *command) {
    printf("$> %s\n", command);
    system(command);
}
