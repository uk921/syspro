#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 64

void execute_single_command(char *cmd) {
    char *args[MAXARG];
    int background = 0;
    char *infile = NULL, *outfile = NULL;
    int arg_count = 0;

    char *saveptr;
    char *token = strtok_r(cmd, " \t\n\r", &saveptr);
    
    while (token != NULL) {
        if (strcmp(token, "&") == 0) {
            background = 1;
        } else if (strcmp(token, ">") == 0) {
            outfile = strtok_r(NULL, " \t\n\r", &saveptr);
        } else if (strcmp(token, "<") == 0) {
            infile = strtok_r(NULL, " \t\n\r", &saveptr);
        } else {
            args[arg_count++] = token;
        }
        token = strtok_r(NULL, " \t\n\r", &saveptr);
    }
    args[arg_count] = NULL;

    if (arg_count == 0) return;

    if (fork() == 0) {
        if (infile) {
            int fd = open(infile, O_RDONLY);
            dup2(fd, 0);
            close(fd);
        }
        if (outfile) {
            int fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0660);
            dup2(fd, 1);
            close(fd);
        }
        execvp(args[0], args);
        exit(1);
    } else {
        if (!background) {
            wait(NULL);
        }
    }
}

int main() {
    char line[MAXLINE];

    while (1) {
        printf("[shell] ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) break;

        char *saveptr;
        char *cmd = strtok_r(line, ";", &saveptr);
        
        while (cmd != NULL) {
            execute_single_command(cmd);
            cmd = strtok_r(NULL, ";", &saveptr);
        }
    }
    return 0;
}
