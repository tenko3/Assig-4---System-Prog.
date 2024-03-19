#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void mySigHandler(int signum) {
    printf("Received signal %d\n", signum);
}

int main() {
    // Install signal handler for SIGINT and SIGQUIT
    signal(SIGINT, mySigHandler);
    signal(SIGQUIT, mySigHandler);

    while(1) {
        printf("Give me a signal\n");
        sleep(1);
    }

    return 0;
}


