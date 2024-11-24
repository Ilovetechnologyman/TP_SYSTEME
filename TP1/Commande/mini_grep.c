#include "../mini_lib.h"
#include <stddef.h>
char *mini_strstr(const char *haystack, const char *needle) {
    if (!*needle) {
        return (char *)haystack;
    }
    for (; *haystack; haystack++) {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && *h == *n) {
            h++;
            n++;
        }
        if (!*n) {
            return (char *)haystack;
        }
    }
    return NULL;
}

char *mini_strchr(const char *str, int c) {
    while (*str != '\0') {
        if (*str == (char)c) {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}


int main(int argc, char *argv[]){
    if (argc != 3) {
        mini_printf("Usage: %s <word> <filename>\n");
        return 1;
    }

    char *word = argv[1];
    char *filename = argv[2];
    char buffer[2048];
    struct MYFILE *file = mini_fopen(filename, 'r');

    if (file == NULL) {
        mini_printf("Could not open file \n");
        return 1;
    }
    mini_fread(buffer, sizeof(char), 2048, file);
    char *line = buffer;
    char *next_line;
    while ((next_line = mini_strchr(line, '\n')) != NULL) {
        *next_line = '\0';
        if (mini_strstr(line, word) != NULL) {
            mini_printf(line);
            mini_printf("\n");
        }
        line = next_line + 1;
    }
    if (mini_strstr(line, word) != NULL) {
        mini_printf(line);
    }
    mini_fclose(file);
    return 0;
}


