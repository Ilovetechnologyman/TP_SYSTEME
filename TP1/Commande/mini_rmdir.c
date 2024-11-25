#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../mini_lib.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        mini_printf( "Usage: %s <directory>\n");
        return EXIT_FAILURE;
    }
    struct stat statbuf;
    if (stat(argv[1], &statbuf) != 0) {
        perror("stat");
        return EXIT_FAILURE;
    }

    if (!S_ISDIR(statbuf.st_mode)) {
        mini_printf("%s is not a directory\n");
        return EXIT_FAILURE;
    }

    if (rmdir(argv[1]) != 0) {
        mini_perror("rmdir");
        return EXIT_FAILURE;
    }

    printf("Directory %s removed successfully\n", argv[1]);
    return EXIT_SUCCESS;
}