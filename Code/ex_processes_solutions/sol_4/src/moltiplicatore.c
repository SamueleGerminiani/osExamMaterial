#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    // Check command line input arguments using 'argc'
    if (argc != 3) {
        // Print a usage message if the number of arguments is not correct
        printf("Usage: %s n m\n", argv[0]);
        return 1;
    }

    // Convert the first and second command-line arguments (argv[1] and argv[2]) to integers.
    // These integers represent the values of 'n' and 'm'.
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    // Calculate the product of 'n' and 'm' and print the result
    printf("The product of %d and %d is: %d\n", n, m, (n * m));

    return 0;
}

