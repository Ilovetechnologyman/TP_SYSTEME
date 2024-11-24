#include "../mini_lib.h"
#include <stddef.h>

int main( int argc, char *argv[ ] ){
    if(argc != 2){
        mini_perror("manque d'argument");
        mini_exit();
    }
    char *filename = argv[1];
    struct MYFILE *file = mini_calloc(sizeof(struct MYFILE *), 1);
    file =  mini_fopen(filename, 'a');
    if(file == NULL){
        mini_perror("Erreur lors de l'ouverture du fichier");
        mini_exit();
    }
    mini_fclose(file);
    return 0;
}