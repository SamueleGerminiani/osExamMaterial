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
    int n = atoi(argv[1]);
    if (n < 0) {
        printf("The number of subprocesses must be > 0!\n");
        return 1;
    }

    // Initialize seed for 'rand' function using 'srand' and 'time'
    srand(0);

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

    int status, res;
    // Get the termination status of the last created subprocess using 'waitpid' and 'WNOHANG' to avoid blocking
    do {
        res = waitpid(pid, &status, WNOHANG);
        if (res == -1)
            errExit("waitpid failed");
    } while (res == 0);

    // Print the exit status of the last subprocess using 'WEXITSTATUS'
    printf("Child %d exited, status=%d\n", pid, WEXITSTATUS(status));

    return 0;
}

