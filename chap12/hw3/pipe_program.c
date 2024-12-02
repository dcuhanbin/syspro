#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void execute_command(const char *command, char *const args[]) {
    if (execvp(command, args) == -1) {
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s command1 arg1 | command2 arg2\n", argv[0]);
        return EXIT_FAILURE;
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return EXIT_FAILURE;
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork failed");
        return EXIT_FAILURE;
    }

    if (pid1 == 0) { // 첫 번째 자식 프로세스
        close(pipe_fd[0]); // 파이프의 읽기 끝 닫기
        dup2(pipe_fd[1], STDOUT_FILENO); // 표준 출력을 파이프의 쓰기 끝으로 연결
        close(pipe_fd[1]);

        char *cmd1_args[] = {argv[1], argv[2], NULL}; // 첫 번째 명령어와 인자
        execute_command(argv[1], cmd1_args);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork failed");
        return EXIT_FAILURE;
    }

    if (pid2 == 0) { // 두 번째 자식 프로세스
        close(pipe_fd[1]); // 파이프의 쓰기 끝 닫기
        dup2(pipe_fd[0], STDIN_FILENO); // 표준 입력을 파이프의 읽기 끝으로 연결
        close(pipe_fd[0]);

        char *cmd2_args[] = {argv[3], argv[4], NULL}; // 두 번째 명령어와 인자
        execute_command(argv[3], cmd2_args);
    }

    // 부모 프로세스: 파이프 닫고 두 자식 프로세스가 종료될 때까지 대기
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return EXIT_SUCCESS;
}

