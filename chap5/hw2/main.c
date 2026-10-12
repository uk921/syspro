#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LINES 100
#define MAX_LEN 256

int main(int argc, char *argv[]) {
    int fd;
    char lines[MAX_LINES][MAX_LEN];
    char ch;
    int line_idx = 0, char_idx = 0;

    if (argc < 2) {
        fprintf(stderr, "How to use: %s file\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    while (read(fd, &ch, 1) > 0) {
        if (ch == '\n') {
            lines[line_idx][char_idx] = '\0'; 
            line_idx++;
            char_idx = 0;
        } else {
            lines[line_idx][char_idx++] = ch;
        }
    }

    if (char_idx > 0) {
        lines[line_idx][char_idx] = '\0';
        line_idx++;
    }

    close(fd);

    for (int i = line_idx - 1; i >= 0; i--) {
        printf("%s\n", lines[i]);
    }

    return 0;
}
