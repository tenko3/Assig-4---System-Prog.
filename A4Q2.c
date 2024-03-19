#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void ctrl_c_handler(int signal) {
    printf("Ctrl+C signal received.\n");
}

int main() {
    
    signal(SIGINT, ctrl_c_handler); // install ctrl c handler
    signal(SIGTSTP, SIG_IGN); // ignore ctrl Z
    
    pid_t child_pid = fork(); // create child proc
    
    if (child_pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) { // child proc
        execl("./donothing", "donothing", NULL); 
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {
        // Inside the parent process
        int status;
        waitpid(child_pid, &status, 0);
        
        // Check if Ctrl+C handler is set back to default
        printf("Ctrl+C handler in parent: %p\n", signal(SIGINT, SIG_DFL));
        
        // Test sending Ctrl+Z signal to the parent process
        printf("Sending Ctrl+Z signal to parent...\n");
        kill(getpid(), SIGTSTP);
        printf("Ctrl+Z signal sent.\n");
    }
    
    return 0;
}

/*

Tests ctrl C by waiting for the child proc to finish so the parent uses signal(...dfl) and prints its address.

Tests ctrl z by first ignoring it within Parent proc so that after child proc finishes, the parent proc sends itself a SIGSTP using kill() function to see if it's being ignored.

*/

