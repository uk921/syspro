#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

void print_file(FILE *fp, int show_line_num, int *line_num) {
    char buffer[MAXLINE];

    if (show_line_num) {
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%d %s", (*line_num)++, buffer);
        }
    } else {
        int c;
        while ((c = fgetc(fp)) != EOF) {
            putchar(c);
        }
    }
}

int main(int argc, char *argv[]) {
    int show_line_num = 0;
    int start_idx = 1;
    int line_num = 1;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        show_line_num = 1;
        start_idx = 2;
    }

    if (argc == start_idx) {
        print_file(stdin, show_line_num, &line_num);
        return 0;
    }

    for (int i = start_idx; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "File %s Open Error\n", argv[i]);
            continue;
        }

        print_file(fp, show_line_num, &line_num);
        fclose(fp);
    }

    return 0;
}
