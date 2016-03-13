#include "../utils.h"
#include <limits.h>

const char *read_trimmed_line(FILE *f, char *into) {
    if (fgets(into, LINE_MAX, f)) {
        TRIM_NEWLINE(into);
        return into;
    }
    return 0;
}
