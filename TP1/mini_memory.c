#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "mini_lib.h"
struct malloc_element * malloc_list = NULL; 

void *mini_calloc(int size_element,int number_element){
    void * element=  sbrk(size_element*number_element);
    if(element == (void *) -1){
        exit(EXIT_FAILURE);
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
    perror("sbrk failed");
    exit(EXIT_FAILURE);
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

extern struct FileNode *open_files; // Declare the external variable

void mini_exit(void) {
    // Flush all open files
    struct FileNode *current = open_files;
    while (current) {
        mini_fflush(current->file);
        current = current->next;
    }
    // Free all allocated memory
    struct malloc_element *temp = malloc_list;
    while (temp != NULL) {
        if(temp->statut == 1){
            mini_free(temp->element);
        }
        temp = temp->next_element;
    }
    _exit(EXIT_FAILURE); // Use _exit to avoid calling mini_exit recursively
}

void mini_memcpy(void *dest, const void *src, int n) {
    char *csrc = (char *)src;
    char *cdest = (char *)dest;
    for (int i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }
}



int mini_atoi(const char *str) {
    int result = 0;
    int sign = 1;

    // Ignore leading whitespaces
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v' || *str == '\f' || *str == '\r') {
        str++;
    }

    // Check for sign
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Convert characters to integer
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    return sign * result;
}
// la fonction free() ne libère va vraiment la mémoire alouée mais l'adresse
// qui fait référence avec le bloc de mémoire


