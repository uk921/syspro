#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i;
    struct stat buf;

    for (i = 1; i < argc; i++) {
        printf("%s: ", argv[i]);

        if (lstat(argv[i], &buf) < 0) {
            perror("lstat()");
            continue;
        }

        if (S_ISREG(buf.st_mode))
            printf("%s\n", "Regular File");
        else if (S_ISDIR(buf.st_mode))
            printf("%s\n", "Directory");
        else if (S_ISCHR(buf.st_mode))
            printf("%s\n", "Character Special File");
        else if (S_ISBLK(buf.st_mode))
            printf("%s\n", "Block Special File");
        else if (S_ISFIFO(buf.st_mode))
            printf("%s\n", "FIFO File");
        else if (S_ISLNK(buf.st_mode))
            printf("%s\n", "Symbolic Link");
        else if (S_ISSOCK(buf.st_mode))
            printf("%s\n", "Socket");
        else
            printf("%s\n", "Unknown File Type");
    }

    exit(0);
}
