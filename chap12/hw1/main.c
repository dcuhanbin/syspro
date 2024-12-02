#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define MAXLINE 100

int main() {
    int pipefd[2];
    pid_t pid;
    char send_msg[MAXLINE], recv_msg[MAXLINE];

    // 파이프 생성
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // 부모 프로세스와 자식 프로세스 분기
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // 자식 프로세스
        close(pipefd[1]); // 쓰기 끝 닫기
        read(pipefd[0], recv_msg, MAXLINE); // 파이프에서 읽기
        printf("Recv: [%d] %s\n", getpid(), recv_msg); // 수신 메시지 출력
        close(pipefd[0]); // 읽기 끝 닫기
    } else { // 부모 프로세스
        close(pipefd[0]); // 읽기 끝 닫기
        sprintf(send_msg, "Hello from PID %d", getpid());
        write(pipefd[1], send_msg, strlen(send_msg) + 1); // 메시지 전송
        printf("Send: [%d] %s\n", getpid(), send_msg); // 송신 메시지 출력
        close(pipefd[1]); // 쓰기 끝 닫기
    }

    return 0;
}

