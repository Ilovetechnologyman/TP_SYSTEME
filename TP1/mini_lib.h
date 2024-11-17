#ifndef MINI_LIB_H
#define MINI_LIB_H
typedef struct malloc_element{
    void * element;
    int taille; 
    int statut;
    void * next_element;
}malloc_element;
void *mini_calloc(int size_element,int number_element);
void mini_free(void* ptr);
void mini_exit();
void mini_printf(char* p);
int mini_scanf(char * buffer,int size_buffer);
int mini_strlen(char *s);
int mini_strcpy(char *s,char *d);
int mini_strcmp(char* s1, char* s2);
#endif