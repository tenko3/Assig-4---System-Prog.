#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void printOrphan(void);

int main() {
    pid_t pid1, pid2;
    
    pid1 = fork(); // fork to create child procs
    if (pid1 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) { // first child proc
        printf("1st child created. PID=%d\n", getpid());
        printf("   becoming orphan\n");
        sleep(1); 
        atexit(printOrphan); // Function to print orphan output
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        // Create the second child process
        pid2 = fork(); // parent proc
        if (pid2 < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) { // child 2 process
            printf("2nd child created. PID=%d\n", getpid());
            printf("    I will be waited for by my parent...\n");
            exit(EXIT_SUCCESS);
        } else { // parent proc waits for second child
            int status;
            waitpid(pid2, &status, 0); // Wait for the second child process
            printf("Parent waited for pid=%d successfully\n", pid2);
            printf("   exit status: %d\n", WEXITSTATUS(status)); // Print child 2 exit status
        }
    }
    
    return 0;
}

void printOrphan(void) { // 
    printf("1st child, PID=%d, PPID=%d orphaned!\n", getpid(), getppid());
}


