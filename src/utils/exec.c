#include "../utils.h"
#include <stdlib.h>

void execute_command(const char *command) {
    LOG_COMMAND(command);
    int status = system(command);
    assert_success_exit(command, status);
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

int get_exit_code(const char *command, int status) {
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status) || WIFSTOPPED(status)) {
        EXIT_SUB_PROCESS_ERROR(command, "child ended by signal", WTERMSIG(status));
    } else {
        EXIT_SUB_PROCESS_ERROR(command, "Unexpected status code", status);
    }
}

void assert_success_exit(const char *command, int status) {
    int code = get_exit_code(command, status);
    if (code)
        EXIT_SUB_PROCESS_ERROR(command, "child exited", code);
}
