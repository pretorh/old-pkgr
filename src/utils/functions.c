#include "../utils.h"

void split_filename(const char *from, char *dir, char *file) {
    const char *found = strrchr(from, '/');
    if (found == NULL) {
        if (dir)
            strcpy(dir, "./");
        if (file)
            strcpy(file, from);
        return;
    }

    int offset = found - from;

    if (dir) {
        strncpy(dir, from, offset);
        dir[offset] = 0;
    }
    if (file) {
        strcpy(file, from + offset + 1);
    }
}
