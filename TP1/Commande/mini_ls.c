#include "../mini_lib.h"
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#define COLOR_RESET "\033[0m"
#define COLOR_GREEN "\033[32m"



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


void print_file_info(struct stat *file_stat,  char *file_name) {
    char permissions[11];
    permissions[0] = (S_ISDIR(file_stat->st_mode)) ? 'd' : '-';
    permissions[1] = (file_stat->st_mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (file_stat->st_mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (file_stat->st_mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (file_stat->st_mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (file_stat->st_mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (file_stat->st_mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (file_stat->st_mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (file_stat->st_mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (file_stat->st_mode & S_IXOTH) ? 'x' : '-';
    permissions[10] = '\0';

    struct passwd *pw = getpwuid(file_stat->st_uid);
    struct group *gr = getgrgid(file_stat->st_gid);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat->st_mtime));
    mini_printf(permissions);
    mini_printf("\t");
    char nlink_str[12];
    mini_sprintf(nlink_str, file_stat->st_nlink);
    mini_printf(nlink_str);
    mini_printf("\t");
    mini_printf(pw->pw_name);
    mini_printf("\t");
    mini_printf(gr->gr_name);
    mini_printf("\t");
    char size_str[20];
    mini_sprintf(size_str, file_stat->st_size);
    mini_printf(size_str);
    mini_printf("\t");
    mini_printf(time_str);
    mini_printf("\t");
    if (file_stat->st_mode & S_IXUSR) {
        mini_printf(COLOR_GREEN);
    }
    mini_printf(file_name);
    if (file_stat->st_mode & S_IXUSR) {
        mini_printf(COLOR_RESET);
    }
    mini_printf("\n");
}

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    dir = opendir(".");
    if (dir == NULL) {
        mini_perror("opendir");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &file_stat) == -1) {
            mini_perror("stat");
            continue;
        }
         if (S_ISDIR(file_stat.st_mode)) {
            continue;
        }

        print_file_info(&file_stat, entry->d_name);
    }

    closedir(dir);
    return 0;
}