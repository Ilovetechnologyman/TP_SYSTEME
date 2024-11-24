#include "../mini_lib.h"
#include <stddef.h>


int main(int argc, char *argv[]){
    if(argc != 2){
        mini_printf("Usage: mini_cat <file>\n");
        return 1;
    }
    struct MYFILE *file = mini_fopen(argv[1], 'r');
    if(file == NULL){
        mini_printf("Error: cannot open file\n");
        mini_exit();
    }
    char buffer[1024];
    size_t bytesRead = mini_fread(buffer, sizeof(char), 1023, file);
    while(bytesRead > 0){
        buffer[bytesRead] = '\0';
        mini_printf(buffer);
        bytesRead = mini_fread(buffer, sizeof(char), 1023, file);
    }
    mini_fclose(file);
    return 0;
}
