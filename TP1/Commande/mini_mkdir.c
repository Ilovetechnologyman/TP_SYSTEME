#include <sys/stat.h>
#include "../mini_lib.h"
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        mini_perror("fichier ne s'ecrit pas");
    }

    const char *dir_name = argv[1];
    if (mkdir(dir_name, 0755) == -1) {
        mini_perror("mkdir");
        return -1;
    }

    mini_printf("Directory '%s' created successfully.\n");
    return 0;
}