#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 100

/* 파이프를 통해 자식에서 실행되는 명령어 출력을 받아 프린트 */
int main(int argc, char* argv[])
{
    int n, pid, fd[2];
    char line[MAXLINE];

    pipe(fd);   /* 파이프 생성 */

    if ((pid = fork()) == 0) {    // 자식 프로세스
        close(fd[0]);            // 파이프의 읽기 끝 닫기
        dup2(fd[1], 1);          // 표준출력을 파이프 쓰기로 연결
        close(fd[1]);            // 쓰기 끝 닫기
        printf("Hello! pipe\n"); // 메시지 출력
        printf("Bye! pipe\n");
    } else {                     // 부모 프로세스
        close(fd[1]);            // 파이프의 쓰기 끝 닫기
        printf("자식 프로세스로부터 받은 결과\n");
        while ((n = read(fd[0], line, MAXLINE)) > 0) // 파이프에서 읽기
            write(STDOUT_FILENO, line, n);          // 표준 출력으로 쓰기
    }

    exit(0);                      // 프로그램 종료
}

