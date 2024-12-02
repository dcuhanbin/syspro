#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int pid;
void alarmHandler();

/* 명령줄 인수로 받은 명령어 실행에 제한 시간을 둔다. */
int main(int argc, char *argv[]) {
    int child, status, limit;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <time_limit> <command> [args...]\n", argv[0]);
        exit(1);
    }

    signal(SIGALRM, alarmHandler);
    sscanf(argv[1], "%d", &limit);
    alarm(limit);

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        execvp(argv[2], &argv[2]);
        fprintf(stderr, "%s: Cannot execute\n", argv[2]);
        exit(1);
    } else {
        child = wait(&status);
        printf("[%d] child process %d exit\n", getpid(), pid);
    }
    return 0;
}

void alarmHandler() {
    printf("[alarm] child process %d time out\n", pid);
    kill(pid, SIGINT);
}

