#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "mini_lib.h"
struct malloc_element * malloc_list = NULL; 
extern int errno;
void *mini_calloc(int size_element,int number_element){
    void * element=  sbrk(size_element*number_element);
    if(element == (void *) -1){
        errno = 2;
        mini_perror("Erreur: pas de mémoire disponible\n");
        mini_exit();
    }
    for(int i=0; i < size_element*number_element;i++){
        ((char *)element)[i] = '\0';
    }
    struct malloc_element *temp = malloc_list;
    while(temp!= NULL){ 
        if(temp->statut == 0 && (temp->taille >= size_element* number_element )){
           temp->element = element;
           temp->statut = 1;
           return element;
        }
        temp = temp->next_element;
    }

    malloc_element * tampon = sbrk(sizeof(malloc_element));
    if (tampon == (void *)-1) {
        errno = 2;
        mini_perror("Erreur: pas de mémoire disponible\n");
        
    }
    tampon->element = element;
    tampon->taille = size_element*number_element;
    tampon->statut = 1;
    tampon->next_element = malloc_list;
    malloc_list = tampon;
    return element;
}

void mini_free(void* ptr){
    struct malloc_element * temp = malloc_list;
    if(ptr==NULL){
        printf("il n'y a rien a libérer ! \n");
        return;
    }
    while(temp!= NULL){
        if(temp->element == ptr){
            temp->statut = 0;
            return;
        }
        temp = temp->next_element;
    }
    printf("la partition n'a pas été trouvé \n");
}

extern struct FileNode *open_files; 

void mini_exit(void) {
    
    struct FileNode *current = open_files;
    while (current) {
        mini_fflush(current->file);
        current = current->next;
    }
   
    struct malloc_element *temp = malloc_list;
    while (temp != NULL) {
        if(temp->statut == 1){
            errno = 2;
            mini_free(temp->element);
        }
        temp = temp->next_element;
    }
    current = open_files;
    while (current != NULL) {
        if (mini_fclose(current->file) == -1) {
            errno = 3;
            mini_perror("Erreur: le fichier n'a pas pu être fermé\n");
        }
        current = current->next;
    }
    _exit(errno); 
}

void mini_memcpy(void *dest, const void *src, int n) {
    if(dest == NULL || src == NULL){
        errno = 1;
        mini_perror("Erreur: pointeur NULL\n");
    }
    char *csrc = (char *)src;
    char *cdest = (char *)dest;
    for (int i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }
}



int mini_atoi(const char *str) {
    int result = 0;
    int sign = 1;
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v' || *str == '\f' || *str == '\r') {
        str++;
    }

    
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    return sign * result;
}



