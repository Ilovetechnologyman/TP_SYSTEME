#include "mini_lib.h"
#include <unistd.h>

#define SUCCESS 0 
#define NO_POINTER 1
#define NO_MEMORY 2
#define WRITE_ERROR 3
#define READ_ERROR 4
#define OPEN_ERROR 5
#define CLOSE_ERROR 6
#define FLUSH_ERROR 7
#define NO_FILE 8
#define OVERFLOW 9



int errno =0; //code erreur 
int BUF_SIZE = 1024;
char *buffer=NULL;
int ind= -1;

void mini_printf(char* p){
    if (ind == -1) {
        buffer = mini_calloc(sizeof(* buffer),BUF_SIZE);
        ind = 0;
    }
    int i=0;
    while (*(p+i) != '\0') {
        if(*(p+i) == '\n'){
            write(1,buffer,ind);
            for(int j=0;j<ind;j++){
            *(buffer+j) = '\0';
            }
            ind = 0;
        }
        if(ind == BUF_SIZE){
            write(1,buffer,ind);
            for(int j=0;j<ind;j++){
            *(buffer+j) = '\0';
            }
            ind = 0;
        }
        
        *(buffer+ind) = *(p+i);
        ind++;
        i++;
    }
    if (ind > 0) {
        write(1, buffer, ind);
        for (int j = 0; j < ind; j++) {
            *(buffer + j) = '\0';
        }
        ind = 0;
    }
    ind=-1;
    mini_free(buffer);
}

int mini_scanf(char * buffer,int size_buffer){
    if(buffer == NULL){
        errno = 1;
        mini_perror("Erreur: pointeur NULL\n");
    }
    return read(1,buffer,size_buffer);
}

int mini_strlen(char *s){
    if(s == NULL){
        errno = 1;
        mini_perror("Erreur: pointeur NULL\n");
    }
    int i=0;
    while(*(s+i) != '\0'){
        i++;
    }
    return i;
}

int mini_strcpy(char *s, char *d) {
    int i = 0;
    while (*(s + i) != '\0') {
        *(d + i) = *(s + i);
        i++;
    }
    *(d + i) = '\0';
    return i;
}

int mini_strcmp(char* s1, char* s2){
    if(mini_strlen(s1)==mini_strlen(s2)){
        return 0;
    }
    if(mini_strlen(s1) > mini_strlen(s2)){
        return 1;
    }
    return 2;
}



void mini_perror(char * message){
    mini_printf(message);
    switch(errno){
        case NO_POINTER:
            mini_printf("Erreur: pointeur NULL\n");
            break;
        case NO_MEMORY:
            mini_printf("Erreur: pas de mémoire disponible\n");
            break;
        case WRITE_ERROR:
            mini_printf("Erreur: écriture impossible\n");
            break;
        case READ_ERROR:
            mini_printf("Erreur: lecture impossible\n");
            break;
        case OPEN_ERROR:
            mini_printf("Erreur: ouverture impossible\n");
            break;
        case CLOSE_ERROR:
            mini_printf("Erreur: fermeture impossible\n");
            break;
        case FLUSH_ERROR:
            mini_printf("Erreur: vidage impossible\n");
            break;
        case NO_FILE:
            mini_printf("Erreur: fichier inexistant\n");
            break;
        case OVERFLOW:
            mini_printf("Erreur: débordement\n");
            break;
        default:
            mini_printf("Erreur inconnue\n");
            break;
    }
}