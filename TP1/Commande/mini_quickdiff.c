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
int mini_fgets(char *buf, int buf_size, struct MYFILE *file) {
    int i = 0;
    char c;
    while (i < buf_size - 1) {
        if (mini_fread(&c, 1, 1, file) <= 0) {
            break;
        }
        buf[i++] = c;
        if (c == '\n') {
            break;
        }
    }
    buf[i] = '\0';
    return i;
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
    int src_index = 0, dest_index = 0;
    int line_number = 1;

    while (1) {
        src_read = mini_fread(src_buf, 1, sizeof(src_buf) - 1, src_fd);
        dest_read = mini_fread(dest_buf, 1, sizeof(dest_buf) - 1, dest_fd);

        if (src_read <= 0 && dest_read <= 0) {
            break; // End of both files
        }

        src_buf[src_read] = '\0';
        dest_buf[dest_read] = '\0';

        while (src_index < src_read && dest_index < dest_read) {
            char *src_line_start = &src_buf[src_index];
            char *dest_line_start = &dest_buf[dest_index];

            // Find the end of the current line in both buffers
            while (src_index < src_read && src_buf[src_index] != '\n') {
                src_index++;
            }
            while (dest_index < dest_read && dest_buf[dest_index] != '\n') {
                dest_index++;
            }

            // Null-terminate the lines
            if (src_index < src_read) {
                src_buf[src_index] = '\0';
                src_index++;
            }
            if (dest_index < dest_read) {
                dest_buf[dest_index] = '\0';
                dest_index++;
            }

            // Compare the lines
            if (mini_memcmp(src_line_start, dest_line_start, src_index - (src_line_start - src_buf)) != 0) {
                write(1, src_line_start, src_index - (src_line_start - src_buf));
                write(1, "\n", 1);
                write(1, dest_line_start, dest_index - (dest_line_start - dest_buf));
                write(1, "\n", 1);
            }

            line_number++;
        }

        // Reset indices for the next read
        src_index = 0;
        dest_index = 0;
    }

    mini_fclose(src_fd);
    mini_fclose(dest_fd);

    return 0;
}