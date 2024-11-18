#include "mini_lib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
    fichier_retourner->fd= open(file,mode);
} 