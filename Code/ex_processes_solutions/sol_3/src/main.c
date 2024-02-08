#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "errExit.h"

#define BUFFER_SZ 150

int main(int argc, char *argv[]) {

    // Get the username of the current user using 'getenv'
    char *username = getenv("USER");
    if (username == NULL)
        username = "unknown";

    // Get the home directory of the user using 'getenv'
    char *homeDir = getenv("HOME");
    if (homeDir == NULL) {
        printf("Unknown home directory\n");
        exit(0);
    }

    // Get the current process's working directory using 'getcwd'
    char buffer[BUFFER_SZ];
    if (getcwd(buffer, sizeof(buffer)) == NULL) {
        printf("getcwd failed\n");
        exit(1);
    }

    // Check if the current process's working directory is a subdirectory of
    // the user's home directory using 'strncmp'
    int subDir = strncmp(buffer, homeDir, strlen(homeDir));

    if (subDir == 0)
        printf("Dear %s, I am already in the right place!\n", username);
    else {
        // Move the process into the user's home directory using 'chdir'
        if (chdir(homeDir) == -1)
            errExit("chdir failed");

        // Create an empty file using 'open'
        int fd = open("empty_file.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd == -1)
            errExit("open failed");

        // Close the file descriptor of the empty file using 'close'
        if (close(fd) == -1)
            errExit("close failed");

        printf("Dear %s, I am now inside your home directory!\n", username);
    }

    return 0;
}

