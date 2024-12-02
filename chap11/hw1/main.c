#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h> // For sleep

void alarmHandler(int signo); // Signal handler prototype

int main() {
    int N = 5; // Number of seconds before sending SIGALRM

    // Set up the signal handler for SIGALRM
    signal(SIGALRM, alarmHandler);

    // Set the alarm for N seconds
    alarm(N);

    short i = 0;
    while (1) {
        sleep(1);
        i++;
        printf("%d second\n", i);
    }

    return 0;
}

// Handler for SIGALRM signal
void alarmHandler(int signo) {
    printf("Wake up\n");
    exit(0); // Exit the program when the alarm triggers
}

