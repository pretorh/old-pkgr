#include "../utils.h"

int split_filename(const char *from, char *dir, char *file) {
    const char *found = strrchr(from, '/');
    if (found == NULL) {
        if (dir)
            strcpy(dir, "./");
        if (file)
            strcpy(file, from);
        return 0;
    }
    int offset = found - from;

    if (dir) {
        strncpy(dir, from, offset);
        dir[offset] = 0;
    }
    if (file) {
        strcpy(file, from + offset + 1);
    }

    return 1;
}
