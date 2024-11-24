#ifndef MINI_LIB_H
#define MINI_LIB_H
typedef struct malloc_element{
    void * element;
    int taille; 
    int statut;
    struct malloc_element * next_element;
}malloc_element;
typedef struct FileNode {
    struct MYFILE *file;
    struct FileNode *next;
} FileNode;
void *mini_calloc(int size_element,int number_element);
void mini_free(void* ptr);
void mini_exit();
void mini_printf(char* p);
int mini_scanf(char * buffer,int size_buffer);
int mini_strlen(char *s);
int mini_strcpy(char *s,char *d);
int mini_strcmp(char* s1, char* s2);
void mini_perror(char * message);
struct MYFILE* mini_fopen(char* file, char mode);
int mini_fread(void *buffer, int size_element, int number_element, struct MYFILE *file);
void mini_memcpy(void *dest, const void *src, int n);
int mini_fwrite(void *buffer,int size_element,int number_element,struct MYFILE *file);
int mini_fflush(struct MYFILE *file);
int mini_fclose(struct MYFILE * file);
int mini_fgetc(struct MYFILE *file);
int mini_fputc(struct MYFILE *file,char c);
int mini_atoi(const char *str);

#endif