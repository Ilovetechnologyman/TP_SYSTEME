#include "../mini_lib.h"
#include <stddef.h>


int main(int argc, char *argv[]){
    if (argc != 3) {
        mini_printf("Usage: %s <word> <filename>\n");
        return 1;
    }

    char *word = argv[1];
    char *filename = argv[2];
    char line[256];
    struct MYFILE *file = mini_fopen(filename, "r");

    if (file == NULL) {
        mini_printf("Could not open file \n");
        return 1;
    }

    while (mini_fgets(line, sizeof(line), file)) {
        if (mini_strstr(line, word)) {
            mini_printf(line);
        }
    }

    mini_fclose(file);
    return 0;
}