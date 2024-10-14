#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *fp1, *fp2;
    char c;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        return 1;
    }

    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
        return 2;
    }

    fp2 = fopen(argv[2], "w");
    if (fp2 == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", argv[2]);
        fclose(fp1);
        return 3;
    }

    while ((c = fgetc(fp1)) != EOF) {
        fputc(c, fp2);
    }

    fclose(fp1);
    fclose(fp2);

    printf("File copied successfully from %s to %s\n", argv[1], argv[2]);
    return 0;
}

