#include "../mini_lib.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        mini_printf("Usage: %s <mode> <file>\n");
        return 1;
    }

    mode_t mode = strtol(argv[1], NULL, 8);
    if (chmod(argv[2], mode) < 0) {
        mini_perror("chmod");
        return 1;
    }

    return 0;
}