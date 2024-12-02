#include <stdio.h>
#include <stdlib.h>  // exit() 사용을 위해 필요
#include <signal.h>

void alarmHandler(int signo);  // 올바른 함수 선언

/* 알람 시그널을 처리한다. */
int main() {
    signal(SIGALRM, alarmHandler);  // SIGALRM에 대한 핸들러 설정
    alarm(5);                       // 알람 시간 설정: 5초 후 SIGALRM 발생

    short i = 0;
    while (1) {
        sleep(1);
        i++;
        printf("%d second\n", i);
    }

    return 0;  // 실행되지 않음
}

/* 알람 시그널 처리 함수 */
void alarmHandler(int signo) {
    printf("Wake up\n");
    exit(0);  // 프로그램 종료
}

