#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// SIGINT 처리 함수
void intHandler(int signo);

/* 인터럽트 시그널을 처리한다. */
int main() {
    // SIGINT 신호에 대해 intHandler를 호출하도록 설정
    signal(SIGINT, intHandler);

    while (1) {
        pause(); // 신호가 올 때까지 대기
    }

    printf("end\n"); // 실행되지 않음 (pause가 무한 대기하므로)
    return 0;
}

void intHandler(int signo) {
    printf("Interrupt signal received.\n");
    printf("Signal number: %d\n", signo);
    exit(0); // 프로그램 종료
}

