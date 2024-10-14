#include <stdio.h>
#define MAXLINE 80

int main(int argc, char *argv[]) {
    FILE *fp;
    int line = 0;
    char buffer[MAXLINE];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
        return 2;
    }

    while (fgets(buffer, MAXLINE, fp) != NULL) {
        line++;
        printf("%3d %s", line, buffer);
    }

    fclose(fp);
    return 0;
}

