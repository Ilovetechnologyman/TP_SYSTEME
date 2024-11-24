#include "../mini_lib.h"
#include <stddef.h>

extern int errno;

void mini_sprintf(char *buffer, int value) {
    char temp[12]; 
    int i = 0;
    int is_negative = 0;

    if (value < 0) {
        is_negative = 1;
        value = -value;
    }
    do {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    } while (value > 0);

    if (is_negative) {
        temp[i++] = '-';
    }

    int j = 0;
    while (i > 0) {
        buffer[j++] = temp[--i];
    }
    buffer[j] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        mini_printf("Usage: <filename>\n");
        return 1;
    }

    struct MYFILE *fd = mini_fopen(argv[1], 'r');
    if (fd == NULL) {
        mini_perror("Error opening file");
        return 1;
    }

    char buffer[1024];
    int bytesRead;
    int wordCount = 0;
    int inWord = 0;

    while ((bytesRead = mini_fread(buffer, sizeof(char), 1024, fd)) > 0) {
        for (int i = 0; i < bytesRead; i++) {
            if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') {
                if (inWord) {
                    wordCount++;
                    inWord = 0;
                }
            } else {
                inWord = 1;
            }
        }
    }

    if (inWord) {
        wordCount++;
    }
    mini_fclose(fd);

    // Convert the word count to a string
    char wordCountStr[12]; // Enough to hold all numbers up to 32-bit int
    mini_sprintf(wordCountStr, wordCount);

    // Print the word count
    mini_printf(wordCountStr);

    return 0;
}