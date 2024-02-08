#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "errExit.h"

const char *fileName = "myfile1";

int main(int argc, char *argv[]) {
    // Check command line input arguments
    if (argc <= 1) {
        printf("Usage: %s cmd [arguments]\n", argv[0]);
        return 0;
    }

    switch (fork()) {
        case -1: {
            // In the parent process, handle the fork failure using 'errExit'
            errExit("fork failed");
        }
        case 0: {
            // In the child process:

            // Close the standard output and error stream (file descriptors 1 and 2)
            close(STDOUT_FILENO);  // Close file descriptor 1
            close(STDERR_FILENO);  // Close file descriptor 2

            // Create a new file. The value returned by 'open' will be 1 as it is the lowest available file descriptor index.
            int fd =
                open(fileName, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

            if (fd == -1) errExit("open failed");

            // Clone file descriptor 1. The value returned by 'dup' will be 2 as it is the lowest available file descriptor index.
            dup(fd);
            // Both file descriptors 1 and 2 are now pointing to the created/ file.


            // Replace the current process image with a new process image using 'execvp'
            execvp(argv[1], &argv[1]);
            // If 'execvp' fails, handle the error using 'errExit'
            errExit("execvp failed");
        }
        default: {
            // In the parent process:

            int status;
            // Wait for the termination of the child process
            if (wait(&status) == -1) errExit("wait failed");

            // Print the exit status of the executed command
            printf("Command %s exited with status %d\n", argv[1],
                   WEXITSTATUS(status));
        }
    }

    return 0;
}

