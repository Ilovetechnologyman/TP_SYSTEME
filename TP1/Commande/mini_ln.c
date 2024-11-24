#include "../mini_lib.h"
#include <unistd.h>


int main(int argc, char *argv[]){
    if (argc != 3) {
        mini_printf("Usage: %s <source> <destination>\n");
        return 1;
    }

    if (symlink(argv[1], argv[2]) == -1) {
        mini_perror("symlink");
        return 1;
    }

    return 0;
}