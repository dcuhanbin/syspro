#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define MAXLINE 100

int main() {
    int fd, length;
    char message[MAXLINE];

    // 이름 있는 파이프(myPipe) 생성
    mkfifo("myPipe", 0666);

    // named pipe(myPipe) 읽기 전용으로 열기
    fd = open("myPipe", O_RDONLY);

    // 파이프에서 메시지 읽기
    while ((length = read(fd, message, MAXLINE)) > 0) {
        printf("%s\n", message); // 읽은 메시지 출력
    }

    close(fd); // 파이프 닫기
    unlink("myPipe"); // 파이프 삭제
    return 0;
}
