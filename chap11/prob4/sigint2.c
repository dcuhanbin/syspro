#include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct sigaction newact;
struct sigaction oldact;

void sigint_handler(int signo);

int main(void) {
    // SIGINT 시그널 핸들러 설정
    newact.sa_handler = sigint_handler; // 시그널 처리기 지정
    sigfillset(&newact.sa_mask);        // 모든 신호 차단 (SIGINT 처리 중)
    newact.sa_flags = 0;                // 추가 플래그 없음

    // SIGINT의 새로운 액션 설정 및 이전 액션 저장
    sigaction(SIGINT, &newact, &oldact);

    while (1) {
        printf("Type Ctrl-C!\n");
        sleep(1);
    }

    return 0;
}

/* SIGINT 처리 함수 */
void sigint_handler(int signo) {
    printf("Signal number %d caught.\n", signo);
    printf("Press Ctrl-C again to exit.\n");

    // 기존 SIGINT 처리기로 복구
    sigaction(SIGINT, &oldact, NULL);
}

