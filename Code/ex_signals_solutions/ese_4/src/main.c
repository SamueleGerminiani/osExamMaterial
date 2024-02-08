#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "errExit.h"

pid_t child1, child2;

// The sigHandler is the signal handler for the signal SIGINT
// The function gently terminates the two sub processes by sending SIGTERM
void sigHandler(int sig) {
    kill(child1, SIGTERM);
    kill(child2, SIGTERM);
    // eventually the parent process termiantes
    exit(0);
}

int main (int argc, char *argv[]) {
    // create the first process (child1)
    child1 = fork();
    if (child1 == -1)
        errExit("fork failed");

    if (child1 == 0) {
        // the infinite loop simulate a working task
        while (1) {
            sleep(1);
            printf("I'm the child1, playing...\n");
        }
    }

    // create the process (child2)
    child2 = fork();
    if (child2 == -1)
        errExit("fork failed");

    if (child2 == 0) {
        // the second process simulates an asincronous event, which suspends
        // the working task
        while (1) {
            sleep(3);
            printf("I'm child 2, disturbing child1...\n");
            // send SIGSTOP to child 1
            if (kill(child1, SIGSTOP) == -1)
                errExit("kill failed");
        }
    }

    // Set a signal handler to manage SIGINT signal sent by user
    if (signal(SIGINT, sigHandler) == SIG_ERR)
        errExit("change signal handler failed");

    int status;
    while (1) {
        // The parent process implements a monitoring process, which resets
        // the normal execution of the working process (child1)
        sleep(5);
        // monitor status of child 1 (see waitpid options)
        pid_t p = waitpid(child1, &status, WUNTRACED | WNOHANG);

        if (p == -1)
            errExit("waitPid failed");
        else if (p != 0 && WIFSTOPPED(status)) {
            // if child1 process is stopped, then the parent resumes it
            printf("<parent> Resume child1...\n");
            // send SIGCONT to child1
            if (kill(child1, SIGCONT) == -1)
                errExit("kill failed");
        }
    }

    return 0;
}
