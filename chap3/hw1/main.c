#include <stdio.h>
#include <string.h>

#define MAXLINE 100
#define NUM_LINES 5

int main() {
    char lines[NUM_LINES][MAXLINE], temp[MAXLINE];
    int i, j;

    for (i = 0; i < NUM_LINES; i++) {
        fgets(lines[i], MAXLINE, stdin);
        lines[i][strcspn(lines[i], "\n")] = '\0';
    }

    for (i = 0; i < NUM_LINES - 1; i++) {
        for (j = i + 1; j < NUM_LINES; j++) {
            if (strlen(lines[i]) < strlen(lines[j])) {
                strcpy(temp, lines[i]);
                strcpy(lines[i], lines[j]);
                strcpy(lines[j], temp);
            }
        }
    }

    for (i = 0; i < NUM_LINES; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}	
