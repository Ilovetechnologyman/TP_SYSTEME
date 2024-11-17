#include "mini_lib.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
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

int mini_strcpy(char *s,char *d){
    int i = 0;
    while(*(d+i) != '\0'){
        *(d+i) = *(s+i);
    }
    return i;
}

int mini_strcmp(char* s1, char* s2){
    if(strlen(s1)==strlen(s2)){
        return 0;
    }
    if(strlen(s1) > strlen(s2)){
        return 1;
    }
    return 2;
}
