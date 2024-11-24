#include "../mini_lib.h"
#include <stddef.h>


int main(int argc, char *argv[ ] ){
    if(argc != 3){
        mini_perror("manque d'argument");
        mini_exit();
    }
    char *source = argv[1];
    char *destination = argv[2];
    struct MYFILE *file_source = mini_calloc(sizeof(struct MYFILE *), 1);
    struct MYFILE *file_destination = mini_calloc(sizeof(struct MYFILE *), 1);
    file_source =  mini_fopen(source, 'r');
    if(file_source == NULL){
        mini_perror("Erreur lors de l'ouverture du fichier source");
        mini_exit();
    }
    file_destination =  mini_fopen(destination, 'w');
    if(file_destination == NULL){
        mini_perror("Erreur lors de l'ouverture du fichier destination");
        mini_exit();
    }
    char buffer[1024];
    int bytes_read = 0;
    while((bytes_read = mini_fread(buffer, sizeof(char), 1024, file_source)) > 0){
        mini_fwrite(buffer, sizeof(char), bytes_read, file_destination);
        mini_fflush(file_destination);
    }
    mini_fclose(file_source);
    return 0;
}