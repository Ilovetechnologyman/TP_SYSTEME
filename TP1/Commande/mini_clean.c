#include "../mini_lib.h"
#include <stddef.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        mini_printf("Usage: <filename>\n");
        return 1;
    }

    struct MYFILE *file = mini_fopen(argv[1], 'w');
    if (file == NULL) {
        mini_perror("Error opening file");
        return 1;
    }

    // Le fichier est maintenant ouvert en mode écriture, ce qui le remet à zéro
    mini_fclose(file);
    return 0;
}