#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd;

    if (argc < 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        exit(1);
    }

    fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    
    if (fd == -1) {
        printf("File Open Error\n");
        exit(1);
    } else {
        printf("File %s Open Success: %d\n", argv[1], fd);
    }

    char *text = "This is a test message written to the file.\n";
    write(fd, text, sizeof(text));

    close(fd);
    exit(0);
}

