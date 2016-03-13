#include "library.h"
#include "../utils.h"

const char *library_get_owner(const char *library, const char *file, char *owner) {
    FILE *f;
    start_pipe(f, "basename $(dirname `grep -l %s %s/**/owns`)", file, library);

    const char *result = read_trimmed_line(f, owner);

    fclose(f);
    return result;
}
