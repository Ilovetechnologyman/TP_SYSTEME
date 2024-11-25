#include "../mini_lib.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdarg.h>
int mini_snprintf(char *str, size_t size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int ret = vsnprintf(str, size, format, args);
    va_end(args);
    return ret;
}

void mini_mv(char *source,  char *destination) {
    // Vérifier si le fichier source existe
    if (access(source, F_OK) != 0) {
        mini_perror("Erreur : le fichier source n'existe pas");
        mini_exit();
    }

    struct stat dest_stat;
    if (stat(destination, &dest_stat) == 0 && S_ISDIR(dest_stat.st_mode)) {
        char *base_name = basename((char *)source);
        char new_destination[2048];
        mini_snprintf(new_destination, 2048, "%s/%s", destination, base_name);
        destination = new_destination;
    }

    // Tenter de renommer (déplacer) le fichier
    if (rename(source, destination) != 0) {
        // Si rename échoue, copier le fichier manuellement
        struct MYFILE *src_fd = mini_fopen(source, 'r');
        if (src_fd == NULL) {
            mini_perror("Erreur lors de l'ouverture du fichier source");
            mini_exit();
        }

        struct MYFILE *dest_fd = mini_fopen(destination, 'w');
        if (dest_fd == NULL) {
            mini_perror("Erreur lors de l'ouverture du fichier de destination");
            mini_fclose(src_fd);
            mini_exit();
        }

        char buffer[1024];
        ssize_t bytes_read, bytes_written;
        while ((bytes_read = mini_fread(buffer, sizeof(char), 1024, src_fd)) > 0) {
            bytes_written = mini_fwrite(buffer, sizeof(char), bytes_read, dest_fd);
            if (bytes_written != bytes_read) {
                mini_perror("Erreur lors de l'écriture dans le fichier de destination");
                mini_fclose(src_fd);
                mini_fclose(dest_fd);
                mini_exit();
            }
        }

        if (bytes_read < 0) {
            mini_perror("Erreur lors de la lecture du fichier source");
            mini_fclose(src_fd);
            mini_fclose(dest_fd);
            mini_exit();
        }

        mini_fclose(src_fd);
        mini_fclose(dest_fd);

        // Supprimer le fichier source
        if (unlink(source) != 0) {
            mini_perror("Erreur lors de la suppression du fichier source");
            mini_exit();
        }
    }

    mini_printf("Le fichier '%s' a été déplacé vers '%s'.\n");
}

int main(int argc, char *argv[]) {
    // Vérifier les arguments de la ligne de commande
    if (argc != 3) {
        mini_printf("Usage: %s <source> <destination>\n");
        return 1;
    }

    mini_mv(argv[1], argv[2]);
    return 0;
}