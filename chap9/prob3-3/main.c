#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int child, pid, status;

    if (argc < 2) {
        fprintf(stderr, "사용법: %s <명령어> [인자...]\n", argv[0]);
        exit(1);
    }

    pid = fork();
    
    if (pid < 0) {
        fprintf(stderr, "fork 실패\n");
        exit(1);
    } else if (pid == 0) {
        execvp(argv[1], &argv[1]);
        fprintf(stderr, "%s: 실행 불가\n", argv[1]);
        exit(1);
    } else {
        child = wait(&status);
        printf("[%d] child process %d end\n", getpid(), pid);
        printf("\tend code %d\n", status >> 8);
    }

    return 0;
}
