#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void alarmRinger(int signum) {
    printf("Ding!\nDone!\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        
        exit(EXIT_FAILURE);
    }

    int seconds = atoi(argv[1]); // get seconds from command line

    pid_t child_pid = fork();
    if (child_pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) { // child proc
        sleep(seconds);
        kill(getppid(), SIGALRM); // Send SIGALRM to parent proc
        exit(EXIT_SUCCESS);
    } else { // parent proc
        printf("alarm application running\n");
        printf("waiting for alarm to go off\n");
        
        signal(SIGALRM, alarmRinger); // install handler for SIGALRM
        
        pause(); // pause until signal recieved
        
    }

    return 0;
}


