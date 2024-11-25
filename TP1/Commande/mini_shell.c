#include "../mini_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

extern int errno;
void mini_cd(char *path) {
    if (chdir(path) != 0) {
        mini_perror("mini_cd failed");
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    while (1) {
        mini_printf("mini_shell> ");
        ssize_t bytes_read = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH - 1);
        if (bytes_read < 0) {
            mini_perror("read failed");
            continue;
        }

        command[bytes_read] = '\0';
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            break;
        }

        // Handle internal command mini_cd
        if (strncmp(command, "mini_cd ", 8) == 0) {
            char *path = command + 8;
            mini_cd(path);
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            mini_perror("fork failed");
            continue;
        }

        if (pid == 0) {
            execlp(command, command, (char *)NULL);
            mini_perror("execlp failed");
            _exit(EXIT_FAILURE);
        } else {
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}