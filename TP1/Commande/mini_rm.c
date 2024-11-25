#include "../mini_lib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        mini_printf("Usage: %s <file>\n");
        return 1;
    }

    const char *filepath = argv[1];
    struct stat path_stat;
    if (stat(filepath, &path_stat) != 0) {
        mini_perror("stat");
        return 1;
    }

    if (!S_ISREG(path_stat.st_mode)) {
        mini_printf("%s is not a regular file\n");
        return 1;
    }

    if (unlink(filepath) != 0) {
        mini_perror("unlink");
        return 1;
    }

    mini_printf("File %s deleted successfully\n");
    return 0;
}