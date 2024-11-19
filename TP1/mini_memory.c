#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "mini_lib.h"
struct malloc_element * malloc_list = NULL; 

void *mini_calloc(int size_element,int number_element){
    printf("on veut %d bytes de sbrk\n", size_element * number_element);
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
           temp->taille = size_element* number_element;
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


void mini_exit(void){
    struct malloc_element *temp = malloc_list;
    while (temp != NULL) {
        if(temp->statut == 1){
            mini_free(temp->element);
        }
        temp = temp->next_element;
    }
    exit(EXIT_SUCCESS);
}
// la fonction free() ne libère va vraiment la mémoire alouée mais l'adresse
// qui fait référence avec le bloc de mémoire


