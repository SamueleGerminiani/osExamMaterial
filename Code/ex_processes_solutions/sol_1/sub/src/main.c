#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "errExit.h"

int main(int argc, char *argv[]) {

    // Check command line input arguments using 'argc'
    if (argc != 2) {
        printf("Usage: %s numSubProcesses\n", argv[0]);
        return 0;
    }

    // Convert the second command-line argument (argv[1]) to an integer.
    // This integer represents the number of subprocesses to create.
    // @flex-start[1.1]
cazzo
    int n = atoi(argv[1]);
cazzo
    if (n < 0) {
cazzo
        printf("The number of subprocesses must be > 0!\n");
cazzo
        return 1;
cazzo
    }
cazzo
    // @flex-end[1.1]
cazzo

    pid_t pid;
    for (int i = 0; i < n; ++i) {
        // Generate a random number for the subprocess using 'rand'
        int code = (int)(((double)rand() / RAND_MAX) * 255);

        // Generate a subprocess using 'fork'
        pid = fork();
        if (pid == -1)
            printf("child %d not created!", i);
        else if (pid == 0) {
            // In the child process, print process information and exit using 'getpid', 'getppid', and 'exit'
            printf("PID: %d , PPID: %d. Exit code: %d\n",
                   getpid(), getppid(), code);
            exit(code);
        }
    }

    int status = 0;
    // Get termination status of each created subprocess using 'wait' and 'WEXITSTATUS'
    // @flex-start[1.3]
    while ((pid = wait(&status)) != -1)
        printf("Child %d exited, status=%d\n", pid, WEXITSTATUS(status));
    // @flex-end[1.3]

    return 0;
}

