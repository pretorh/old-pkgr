#include "../utils.h"
#include <limits.h>

const char *read_trimmed_line(FILE *f, char *into) {
    if (fgets(into, LINE_MAX, f)) {
        TRIM_NEWLINE(into);
        return into;
    }
    return 0;
}

void for_each_line(FILE *f, void *data, LineCallback *callback) {
    char line[LINE_MAX + 1];
    while (read_trimmed_line(f, line)) {
        if (callback(line, data))
            return;
    }
}
