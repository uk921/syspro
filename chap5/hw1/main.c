#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd;
    char savedText[10][100]; 
    char buf;
    int line = 0, col = 0;

    if (argc < 2) {
        fprintf(stderr, "How to use: %s file\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[line][col] = '\0'; 
            line++;
            col = 0;
        } else {
            savedText[line][col] = buf;
            col++;
        }
    }
    
    if (col > 0) {
        savedText[line][col] = '\0';
        line++;
    }

    close(fd);

    printf("File read success\n");
    printf("Total Line : %d\n", line);
    printf("You can choose 1 ~ %d Line\n", line);
    printf("Pls 'Enter' the line to select : ");

    char input[100];
    scanf("%[^\n]", input);

    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < line; i++) {
            printf("%s\n", savedText[i]);
        }
    }
    else if (strchr(input, '-') != NULL) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        for (int i = start; i <= end; i++) {
            if (i >= 1 && i <= line) {
                printf("%s\n", savedText[i - 1]);
            }
        }
    }
    else if (strchr(input, ',') != NULL) {
        char *ptr = strtok(input, ",");
        while (ptr != NULL) {
            int line_num = atoi(ptr);
            if (line_num >= 1 && line_num <= line) {
                printf("%s\n", savedText[line_num - 1]);
            }
            ptr = strtok(NULL, ",");
        }
    }
    else {
        int line_num = atoi(input);
        if (line_num >= 1 && line_num <= line) {
            printf("%s\n", savedText[line_num - 1]);
        }
    }

    return 0;
}
