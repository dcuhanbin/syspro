#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 100

int main() {
    int fd, length, i;
    char message[MAXLINE];

    // 메시지 작성: 프로세스 ID 포함
    sprintf(message, "Hello from PID %d", getpid());
    length = strlen(message) + 1;

    // named pipe(myPipe) 열기 시도
    do {
        fd = open("myPipe", O_WRONLY);
        if (fd == -1) sleep(1); // 열리지 않으면 1초 대기
    } while (fd == -1);

    // 메시지를 3번 파이프에 쓰기
    for (i = 0; i < 3; i++) {
        write(fd, message, length);
        sleep(3); // 3초 대기
    }

    close(fd); // 파이프 닫기
    return 0;
}
