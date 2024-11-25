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
    int read_max;
}MYFILE;
extern int errno;
FileNode *open_files = NULL;

void add_open_file(MYFILE *file) {
    FileNode *node = mini_calloc(sizeof(FileNode), 1);
    node->file = file;
    node->next = open_files;
    open_files = node;
}

void remove_open_file(MYFILE *file) {
    FileNode **current = &open_files;
    while (*current) {
        if ((*current)->file == file) {           
            FileNode *to_remove = mini_calloc(sizeof(FileNode *), 1); 
            to_remove = *current;
            *current = (*current)->next;
            mini_free(to_remove);
            return;
        }
        current = &((*current)->next);
    }
}

MYFILE* mini_fopen(char* file, char mode){
    MYFILE * fichier_retourner=NULL;
    fichier_retourner = mini_calloc(sizeof(MYFILE), 1);
    fichier_retourner->buffer_read = NULL;
    fichier_retourner->buffer_write = NULL;
    fichier_retourner->ind_read = -1;
    fichier_retourner->ind_write = -1;
    switch (mode)
    {
    case 'r':
        fichier_retourner->fd = open(file,O_RDONLY);
        if(fichier_retourner->fd ==-1){
            errno = 5;
            mini_perror("le fichier n'a pas pu être ouver \n");
            mini_exit();
        }
        break;
    case 'w':
        fichier_retourner->fd = open(file,O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if(fichier_retourner->fd ==-1){
            errno = 5;
            mini_perror("le fichier n'a pas pu être ouver \n");
            mini_exit();
        }
        break;
    case 'b':
        fichier_retourner->fd = open(file,O_RDWR);
        if(fichier_retourner->fd ==-1){
            errno = 5;
            mini_perror("le fichier n'a pas pu être ouver \n");
            mini_exit();
        }
        break;
    case 'a':
        fichier_retourner->fd = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        if(fichier_retourner->fd ==-1){
            errno = 5;
            mini_perror("le fichier n'a pas pu être ouver \n");
            mini_exit();
        }
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
    add_open_file(fichier_retourner);
    return fichier_retourner;
}

int mini_fread(void *buffer, int size_element, int number_element, MYFILE *file) {
    if (file->buffer_read == NULL) {
        file->buffer_read = mini_calloc(size_element, IOBUFFER_SIZE);
        if (file->buffer_read == NULL) {
            errno = 2;
            mini_perror("allocation ratée");
            return -1;
        }
        file->ind_read = 0;
        file->read_max = 0;
    }
    char *output_buffer = (char *)buffer;
    int total_bytes_read = 0;
    while (total_bytes_read < number_element * size_element) {
        if (file->ind_read >= file->read_max) {
            file->read_max = read(file->fd, file->buffer_read, IOBUFFER_SIZE);
            if (file->read_max <= 0) {
                break; // End of file or error
            }
            file->ind_read = 0;
        }
        int bytes_to_copy = (total_bytes_read + (file->read_max - file->ind_read) > number_element * size_element)
                            ? (number_element * size_element - total_bytes_read)
                            : (file->read_max - file->ind_read);
        mini_memcpy(output_buffer + total_bytes_read, (char *)file->buffer_read + file->ind_read, bytes_to_copy);
        file->ind_read += bytes_to_copy;
        total_bytes_read += bytes_to_copy;
    }
    return total_bytes_read / size_element;
}


int mini_fwrite(void *buffer, int size_element, int number_element, MYFILE *file) {
    if (size_element <= 0 || number_element <= 0) {
        return 0;
    }
    if (file->buffer_write == NULL) {
        file->buffer_write = mini_calloc(size_element, IOBUFFER_SIZE);
        if (file->buffer_write == NULL) {
            errno = 2;
            mini_perror("allocation ratée");
            return -1;
        }
        file->ind_write = 0;
    }

    int total_bytes_written = 0;
    char *output_buffer = (char *)buffer;

    while (total_bytes_written < number_element * size_element) {
        if (file->ind_write >= IOBUFFER_SIZE) {
            int bytes_written = write(file->fd, file->buffer_write, IOBUFFER_SIZE);
            if (bytes_written < 0) {
                errno =3;
                mini_perror("écriture ratée");
                return -1;
            }
            file->ind_write = 0; 
        }
        int bytes_to_copy = (total_bytes_written + (IOBUFFER_SIZE - file->ind_write) > number_element * size_element)
                            ? (number_element * size_element - total_bytes_written)
                            : (IOBUFFER_SIZE - file->ind_write);

        mini_memcpy((char *)file->buffer_write + file->ind_write, output_buffer + total_bytes_written, bytes_to_copy);
        file->ind_write += bytes_to_copy;
        total_bytes_written += bytes_to_copy;
    }

    return total_bytes_written / size_element;
}

int mini_fflush(MYFILE *file) {
    if (file->buffer_write == NULL ) {
        return 0;
    }
    int bytes_written = write(file->fd, file->buffer_write, file->ind_write);
    if (bytes_written < 0) {
        errno =3;
        mini_perror("écriture ratée");
        return -1;
    }
    file->ind_write = 0;
    return bytes_written;
}


int mini_fclose(MYFILE * file){
    if(file->buffer_read != NULL){
        mini_free(file->buffer_read);
    }
    if(file->buffer_write != NULL){
        mini_fflush(file);
        mini_free(file->buffer_write);
    }
    int retour = close(file->fd);
    if(retour == -1){
        errno= 6;
        mini_perror("le fichier n'a pas pu être fermé \n");
        return -1;
    }
    remove_open_file(file);
    return 0;
}

int mini_fgetc(MYFILE *file) {
    char c;
    int bytes_read = mini_fread(&c, sizeof(char), 1, file);
    if (bytes_read <= 0) {
        errno = 4;
        mini_perror("Erreur: lecture ratée\n");
        return -1;
    }
    return (unsigned char)c;
}

int mini_fputc(MYFILE *file,char c) {
    char ch = c;
    int bytes_written = mini_fwrite(&ch, 1, 1, file);
    if (bytes_written <= 0) {
        return -1;
    }
    return c;
}