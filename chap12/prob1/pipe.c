#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXLINE 100

/* 파이프를 통해 자식에서 부모로 데이터를 보내는 프로그램 */
int main() 
{
    int n, length, fd[2], pid;
    char message[MAXLINE], line[MAXLINE];

    // 파이프 생성
    if (pipe(fd) == -1) {
        perror("pipe error");
        exit(1);
    }

    // 프로세스 생성
    if ((pid = fork()) == -1) {
        perror("fork error");
        exit(1);
    }

    if (pid == 0) {  /* 자식 프로세스 */
        close(fd[0]);  // 읽기 엔드 닫기
        sprintf(message, "Hello from PID %d\n", getpid());
        length = strlen(message) + 1;  // NULL 문자 포함
        write(fd[1], message, length); // 파이프에 메시지 쓰기
        close(fd[1]);  // 쓰기 엔드 닫기
    } else {  /* 부모 프로세스 */
        close(fd[1]);  // 쓰기 엔드 닫기
        n = read(fd[0], line, MAXLINE); // 파이프에서 메시지 읽기
        if (n > 0) {
            printf("[%d] %s", getpid(), line); // 메시지 출력
        }
        close(fd[0]);  // 읽기 엔드 닫기
    }

    exit(0);
}

