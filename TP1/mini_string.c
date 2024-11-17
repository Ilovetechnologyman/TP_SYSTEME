#include "mini_lib.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int BUF_SIZE = 1024;
char *buffer=NULL;
int ind= -1;


/* 
void mini_printf(char* p){
    void * resultat = mini_malloc(sizeof(buffer),BUF_SIZE);
    int j=0;
    while(p[j] != '\0'){
        j++; //compte les caractère
    }
    for(int i=0;i<BUF_SIZE;i++){
        ((char *)resultat)[i] = p[i%j];
        if(((char *)resultat)[i] == '\n' || ((char *)resultat)[i] == '\0'){
            write(buffer,resultat,ind);
            for(int k=0;k<ind;k++){
                ((char *)resultat)[k] = '\0'; // on libère le tampon
            }
            ind = -1;
        }
        ind++;
    } //le tampon est rempli 
    if(ind == -1){
        mini_exit();
    }
    else{
        write(buffer,resultat,ind);
        for(int k=0;k<ind;k++){
            ((char *)resultat)[k] = '\0'; // on libère le tampon
        }
        mini_exit();
    }
}

*/
void mini_printf(char* p){
    if (ind == -1) {
        buffer = mini_malloc(sizeof(* buffer),BUF_SIZE);
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
    mini_free(buffer);
    ind=-1;
    mini_exit();
}