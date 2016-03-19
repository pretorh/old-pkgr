#include "../utils.h"
#include <stdlib.h>
#include <errno.h>

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

int close_pipe(FILE *f, int allow_non_zero_exit) {
    int status = pclose(f);
    if (status == -1)
        EXIT_SUB_PROCESS_ERROR("(pipe command)", strerror(errno), errno);

    if (allow_non_zero_exit) {
        return get_exit_code("(pipe command)", status);
    } else {
        assert_success_exit("(pipe command)", status);
        return 0;
    }
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

void set_environment_variable(const char *name, const char *value) {
    if (setenv(name, value, 1)) {
        perror("failed to set environment variable");
        EXIT_WITH_ERROR("failed to export %s=%s", name, value);
    }
}
