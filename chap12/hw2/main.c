#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

#define MAXLINE 100

void to_uppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    int pipefd[2];
    pid_t pid1, pid2;
    char input_str[MAXLINE], received_str[MAXLINE];

    // 파이프 생성
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // 첫 번째 자식 프로세스 생성
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return 1;
    }

    if (pid1 == 0) { // 첫 번째 자식 프로세스
        close(pipefd[0]); // 읽기 끝 닫기
        printf("input string: ");
        fgets(input_str, MAXLINE, stdin);
        input_str[strcspn(input_str, "\n")] = '\0'; // 개행 문자 제거
        write(pipefd[1], input_str, strlen(input_str) + 1); // 문자열 전송
        close(pipefd[1]); // 쓰기 끝 닫기
        return 0;
    }

    // 두 번째 자식 프로세스 생성
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        return 1;
    }

    if (pid2 == 0) { // 두 번째 자식 프로세스
        close(pipefd[1]); // 쓰기 끝 닫기
        read(pipefd[0], received_str, MAXLINE); // 문자열 읽기
        to_uppercase(received_str); // 대문자로 변환
        printf("%s\n", received_str); // 변환된 문자열 출력
        close(pipefd[0]); // 읽기 끝 닫기
        return 0;
    }

    // 부모 프로세스
    close(pipefd[0]);
    close(pipefd[1]);

    // 두 자식 프로세스가 종료될 때까지 대기
    wait(NULL);
    wait(NULL);

    printf("Process finished with exit code 0\n");
    return 0;
}

