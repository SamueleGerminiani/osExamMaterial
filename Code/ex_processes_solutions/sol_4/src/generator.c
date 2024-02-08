#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <unistd.h>

#include "errExit.h"

#define MAX_NUM 100

int main(int argc, char *argv[]) {

    // Initialize seed for 'rand' function using 'srand' and 'time'
    srand(time(0));

    // Generate two random numbers between 0 and MAX_NUM
    int n = (int)(((double)rand() / RAND_MAX) * MAX_NUM);
    int m = (int)(((double)rand() / RAND_MAX) * MAX_NUM);

    // Create character arrays to store the converted random numbers as strings
    char nStr[100];
    char mStr[100];

    // Convert the two random numbers to strings using 'sprintf'
    sprintf(nStr, "%d", n);
    sprintf(mStr, "%d", m);

    // Execute the "moltiplicatore" program with the converted random numbers as arguments using 'execl'
    execl("moltiplicatore", "moltiplicatore", nStr, mStr, (char *) NULL);

    // If execl fails, print an error message using 'errExit'
    errExit("execl failed");

    // This return statement will not be reached if execl succeeds
    return 1;
}

