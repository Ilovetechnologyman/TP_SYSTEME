#include "../mini_lib.h"
#include <stddef.h>

extern int errno;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        mini_perror("missing argument");
        return (1);
    }
    int total_length = 0;
    for (int i = 1; i < argc; i++) {
        total_length += mini_strlen(argv[i]) + 1; 
    }

    char *buffer = mini_calloc(sizeof(char *), total_length);
    if (buffer == NULL) {
        errno = 1;
        mini_perror("allocation échouée");
        return (1);
    }

    int i = 1; 
    int pos = 0;
    while(i < argc)
    {
        mini_strcpy(argv[i],buffer + pos);
        pos += mini_strlen(argv[i]);
        buffer[pos] = ' ';
        pos++;
        i++;
    }
    if (pos > 0) {
        buffer[pos - 1] = '\0'; 
    } else {
        buffer[pos] = '\0';
    }
    mini_printf(buffer);
    mini_printf("\n");
    mini_free(buffer);
    return 0;
}