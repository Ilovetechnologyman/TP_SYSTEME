#include "mini_lib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int IOBUFFER_SIZE = 2048;
typedef struct MYFILE{
    int fd;
    void * buffer_read;
    void * buffer_write;
    int ind_read;
    int ind_write;
}MYFILE;


MYFILE* mini_fopen(char* file, char mode){
    MYFILE * fichier_retourner;
    fichier_retourner = mini_calloc(sizeof(MYFILE *),1);
    fichier_retourner->ind_read = -1;
    fichier_retourner->ind_write = -1;
    switch (mode)
    {
    case 'r':
        fichier_retourner->buffer_read = mini_calloc(sizeof(void *),1024);
        fichier_retourner->fd = open(file,O_RDONLY);
        if(fichier_retourner->fd ==-1){
            mini_perror("le fichier n'a pas pu être ouver \n");
            mini_exit();
        }
        fichier_retourner->ind_read= read(fichier_retourner->fd,fichier_retourner->buffer_read,1023);
        break;
    case 'w':
        fichier_retourner->buffer_write = mini_calloc(sizeof(void *),1024);
        fichier_retourner->fd = open(file,O_WRONLY);
        fichier_retourner->ind_write = write(fichier_retourner->fd,fichier_retourner->buffer_write,1023);
        break;
    case 'b':
        fichier_retourner->buffer_read = mini_calloc(sizeof(void *),1024);
        fichier_retourner->buffer_write = mini_calloc(sizeof(void *),1024);
        fichier_retourner->fd = open(file,O_RDWR);
        fichier_retourner->ind_write = write(fichier_retourner->fd,fichier_retourner->buffer_write,1023);
        fichier_retourner->ind_read= read(fichier_retourner->fd,fichier_retourner->buffer_read,1023);
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
}
