#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 64

int main() {
    char line[MAXLINE];
    char *args[MAXARG];
    int status;
    pid_t pid, child;

    while (1) {
        printf("Pls input cmd : ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) break;
        line[strcspn(line, "\n")] = '\0';

        int background = 0;
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '&') {
            background = 1;
            line[len - 1] = '\0';
        }

        char *saveptr;
        int arg_count = 0;
        char *token = strtok_r(line, " \t", &saveptr);

        while (token != NULL) {
            args[arg_count++] = token;
            token = strtok_r(NULL, " \t", &saveptr);
        }
        args[arg_count] = NULL;

        printf("[%d] Parent process start\n", getpid());

        pid = fork();
        if (pid == 0) {
            printf("[%d] child process start\n", getpid());
            execvp(args[0], args);
            exit(1);
        } else {
            if (!background) {
                child = wait(&status);
                if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                    printf("SUCCESS\n\n");
                } else {
                    printf("Parent process end\nExit\n");
                    break;
                }
            } else {
                child = waitpid(pid, &status, 0);
                printf("[%d] child process end %d\n", getpid(), child);
                if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                    printf("SUCCESS\n\n");
                }
            }
        }
    }
    return 0;
}
