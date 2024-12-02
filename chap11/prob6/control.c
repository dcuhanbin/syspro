#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void sigint_handler(int signo);  // 부모 프로세스의 시그널 핸들러

int main() {
    int pid1, pid2, count1 = 0, count2 = 0;

    // 첫 번째 자식 프로세스 생성
    pid1 = fork();
    if (pid1 == 0) {
        while (1) {
            sleep(1);
            printf("child [1] execute: %d\n", ++count1);
        }
    }

    // 두 번째 자식 프로세스 생성
    pid2 = fork();
    if (pid2 == 0) {
        while (1) {
            sleep(1);
            printf("child [2] execute: %d\n", ++count2);
        }
    }

    // 부모 프로세스
    signal(SIGINT, sigint_handler);  // SIGINT 시그널 핸들러 설정

    printf("Parent process: Press Ctrl+C to stop children\n");

    while (1) {
        pause();  // 시그널 대기
    }

    return 0;
}

// SIGINT 핸들러: 자식 프로세스를 종료
void sigint_handler(int signo) {
    printf("\nSIGINT received. Terminating children...\n");
    kill(0, SIGTERM);  // 모든 자식 프로세스 종료
    exit(0);
}

