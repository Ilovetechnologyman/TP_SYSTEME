#include "mini_lib.h"
#include <unistd.h>
#include <errno.h>


extern int errno; //code erreur 
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
    return read(1,buffer,size_buffer);
}

int mini_strlen(char *s){
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
    if(errno != 0){
        mini_printf("erreur");
    }
    else{
        mini_printf("il n'y a pas d'erreur systeme \n");
    }
}