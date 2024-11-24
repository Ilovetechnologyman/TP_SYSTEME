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
    int validation=0;
    int lines = 0;
    mini_fread(buffer, sizeof(char), 2048, file);
    int i,j;
    for (i = 0; i < 2048; i++) {
        if(buffer[i] == '\0'){
            validation = 1; // on a atteint la fin du buffer
            break; 
        }
    }
    if(!validation){ 
        mini_printf("Error: buffer overflow, file too large\n");
        mini_fclose(file);
        mini_exit();
    }
    for(j= i-1; j>0;j--){
        if(buffer[j] == '\n'){
            lines++; // on compte le nombre de lignes à reculons
        }
        if(lines == num_lines){
            break;
        }
    }
    mini_printf(&buffer[i-j]);
    mini_fclose(file);
    return 0;
}