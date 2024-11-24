#include "mini_lib.h"
#include <stdio.h>
#include <string.h>

int main() {
    mini_printf("Starting mini_fwrite test...\n");
    
    // Open the file in write mode
    struct MYFILE *fichier = mini_fopen("lol.txt", 'w');
    if (fichier == NULL) {
        mini_perror("Failed to open file\n");
        return 1;
    }

    // Write to the file
    char *data = "test";
    int bytes_written = mini_fwrite(data, 1, 4, fichier); // Write 4 characters
    mini_printf("Number of bytes written: ");
    printf("%d\n", bytes_written);
    mini_fflush(fichier);
    int t = mini_fputc(fichier, 'a');
    mini_fclose(fichier);
    mini_fopen("lol.txt", 'r');
    int t2 = mini_fgetc(fichier);
    int t3 = mini_fclose(fichier);
    printf("%d %d %d \n", t, t2, t3);

    return 0;
}