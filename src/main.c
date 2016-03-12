#include "settings.h"

int main(int argc, char *argv[]) {
    struct Settings settings = parse_arguments(argc, argv);
    return 0;
}
