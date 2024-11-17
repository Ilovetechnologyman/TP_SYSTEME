#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "mini_lib.h"
#include "debug.h"
struct malloc_element * malloc_list = NULL; 

void *mini_malloc(int size_element,int number_element){
   void * element=  sbrk(size_element*number_element);
   if(element == (void *) -1){
        exit(EXIT_FAILURE);
   }
   for(int i=0; i < size_element*number_element;i++){
        ((char *)element)[i] = '\0';
    }
    while(malloc_list != NULL){ 
        if(malloc_list->statut == 0 && (malloc_list->taille >= size_element* number_element )){
            malloc_list->statut  =1;
            return malloc_list->element ;
        }
        malloc_list = malloc_list->next_element;
    }
    
    malloc_element * tampon = sbrk(sizeof(malloc_element));
    tampon->element = element;
    tampon->taille = size_element*number_element;
    tampon->statut = 1;
    tampon->next_element = malloc_list;
    malloc_list = tampon;
    return element;
}

void mini_free(void* ptr){
    if(ptr==NULL){
        printf("il n'y a rien a libérer ! \n");
        exit(EXIT_FAILURE);
    }
    while(malloc_list != NULL){
        if(malloc_list->element == ptr){
            malloc_list->statut = 0;
            return ;
        }
        malloc_list = malloc_list->next_element;
    }
    printf("la partition n'a pas été trouvé \n");
    exit(EXIT_FAILURE);
}


void mini_exit(){
    exit(EXIT_SUCCESS);

}
// la fonction free() ne libère va vraiment la mémoire alouée mais l'adresse
// qui fait référence avec le bloc de mémoire