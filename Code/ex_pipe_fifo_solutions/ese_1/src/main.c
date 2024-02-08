#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "consumer.h"
#include "errExit.h"
#include "producer.h"

int main(int argc, char *argv[]) {
  // Check command line input arguments.
  // The program only wants a text file
  if (argc != 2) {
    printf("Usage: %s textFile\n", argv[0]);
    return 0;
  }

  int pipeFD[2];

  // Make a new PIPE
  if (pipe(pipeFD) == -1) errExit("pipe failed");

  // Generate a sub process reading a text file token-by-token
  printf("<Consumer> making a subprocess\n");
  switch (fork()) {
    case -1:
      errExit("fork failed");
    case 0: {
      producer(pipeFD, argv[1]);
      exit(0);
    }
    default: {
      consumer(pipeFD);
    }
  }
}
