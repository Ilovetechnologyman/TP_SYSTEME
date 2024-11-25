#include "../mini_lib.h"
#include <aio.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

void mini_mv(const char *source, const char *destination) {
    // Vérifier si le fichier source existe
    if (access(source, F_OK) != 0) {
        perror("Erreur : le fichier source n'existe pas");
        exit(EXIT_FAILURE);
    }

    // Tenter de renommer (déplacer) le fichier
    if (rename(source, destination) != 0) {
        perror("Erreur lors du déplacement du fichier");
        exit(EXIT_FAILURE);
    }

    printf("Le fichier '%s' a été déplacé vers '%s'.\n", source, destination);
}

int main(int argc, char *argv[]) {
    // Vérifier les arguments de la ligne de commande
    if (argc != 3) {
        mini_printf("Usage : %s <source> <destination>\n");
        return -1;
    }

    const char *source = argv[1];
    const char *destination = argv[2];

    // Appeler la fonction mini_mv
    mini_mv(source, destination);

    return EXIT_SUCCESS;
}
