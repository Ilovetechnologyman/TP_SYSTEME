#include "../mini_lib.h"
#include <stddef.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        mini_printf("Usage: mini_head -n <number> <file>\n");
        mini_exit();
    }
    if (argv[1][0] != '-' || argv[1][1] != 'n') {
        mini_printf("Usage: mini_head -n <number> <file>\n");
        mini_exit();
    }

    int num_lines = mini_atoi(argv[2]);
    if (num_lines <= 0) {
        mini_printf("Error: number of lines must be greater than 0\n");
        mini_exit();
    }

    struct MYFILE *file = mini_fopen(argv[3], 'b');
    if (file == NULL) {
        mini_printf("Error: cannot open file\n");
        mini_exit();
    }
    char buffer[2048];
    int lines = 0;
    mini_fread(buffer, sizeof(char), 2048, file);
    for (int i = 0; i < 1024; i++) {
        if (buffer[i] == '\n') {
            lines++;
        }
        if (lines == num_lines) {
            buffer[i + 1] = '\0';
            break;
        }
    }
    mini_printf(buffer);
    mini_fclose(file);
    return 0;
}