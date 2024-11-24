#include "../mini_lib.h"
#include <unistd.h>

#include <stddef.h>


int mini_itoa(int num, char *str) {
    int i = 0;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return 1;
    }
    while (num != 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }
    str[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
    return i;
}

int mini_memcmp(const void *buf1, const void *buf2, size_t count) {
    const unsigned char *p1 = buf1;
    const unsigned char *p2 = buf2;

    for (size_t i = 0; i < count; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        mini_printf("Usage: <file1> <file2>\n");
        return 1;
    }

    struct MYFILE *src_fd = mini_fopen(argv[1], 'r');
    struct MYFILE *dest_fd = mini_fopen(argv[2], 'r');
    if (src_fd == NULL || dest_fd == NULL) {
        mini_perror("Error opening files");
        return 1;
    }

    char src_buf[256], dest_buf[256];
    int src_read, dest_read;
    int line_number = 1;

    while ((src_read = mini_fread(src_buf, 1, sizeof(src_buf), src_fd)) > 0 &&
           (dest_read = mini_fread(dest_buf, 1, sizeof(dest_buf), dest_fd)) > 0) {
        if (mini_strcmp(src_buf, dest_buf) != 0) {
            write(1, "Difference at line ", 19);
            char line_str[10];
            int len = mini_itoa(line_number, line_str);
            write(1, line_str, len);
            write(1, "\n", 1);
            write(1, "File1: ", 7);
            write(1, src_buf, src_read);
            write(1, "\nFile2: ", 8);
            write(1, dest_buf, dest_read);
            write(1, "\n", 1);
        }
        line_number++;
    }

    mini_fclose(src_fd);
    mini_fclose(dest_fd);

    return 0;
}