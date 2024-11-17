#ifndef MINI_LIB_H
#define MINI_LIB_H
typedef struct malloc_element{
    void * element;
    int taille; 
    int statut;
    void * next_element;
}malloc_element;
void *mini_malloc(int size_element,int number_element);
void mini_free(void* ptr);
void mini_exit();
void mini_printf(char* p);
#endif