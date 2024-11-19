#include "mini_lib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int IOBUFFER_SIZE = 2048;
typedef struct MYFILE{
    int fd;
    void * buffer_read;
    void * buffer_write;
    int ind_read;
    int ind_write;
}MYFILE;


MYFILE* mini_fopen(char* file, char mode){
    MYFILE * fichier_retourner=NULL;
    fichier_retourner = mini_calloc(sizeof(MYFILE *),1);
    fichier_retourner->buffer_read = NULL;
    fichier_retourner->buffer_write = NULL;
    fichier_retourner->ind_read = -1;
    fichier_retourner->ind_write = -1;
    switch (mode)
    {
    case 'r':
        fichier_retourner->fd = open(file,O_RDONLY);
        if(fichier_retourner->fd ==-1){
            mini_perror("le fichier n'a pas pu être ouver \n");
            mini_exit();
        }
        break;
    case 'w':
        fichier_retourner->fd = open(file,O_WRONLY);
        break;
    case 'b':
        fichier_retourner->fd = open(file,O_RDWR);
        break;
    case 'a':
        fichier_retourner->fd = open(file, O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP |S_IWGRP | S_IROTH | S_IWOTH);
        break;
    default:
        do {
        mini_printf("Tu n'as pas entré un mode valide, r = read, w = write, b = both, a = append.\n");
        char mode_input;
        mini_scanf(&mode_input, 1);
        mode = mode_input; 
        } while (mode != 'r' && mode != 'w' && mode != 'b' && mode != 'a'); 
        return mini_fopen(file, mode);  
    }
    return fichier_retourner;
}

int mini_fread(void * buffer,int size_element,int number_element, MYFILE * file){
    file->buffer_read = mini_calloc(size_element,IOBUFFER_SIZE);
    file->ind_read = 0;
    size_t decrementation = IOBUFFER_SIZE;
    while(file->ind_read < number_element){
        int sortie = read(file->fd,file->buffer_read + file->ind_read,decrementation);
        if(sortie < 0){
            mini_perror("read raté");
        }
        file->ind_read++;
        decrementation = decrementation - (file->ind_read * size_element);
        if(sortie == 0){
            return file->ind_read;
        }
        mini_strcpy(file->buffer_read + file->ind_read,buffer + file->ind_read);
    }
    return file->ind_read;
}
