#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    printf("Size of \"10\": %d\n", sizeof("10"));

    printf("Size of long: %li\n", sizeof(long));
    printf("Size of int: %d\n", sizeof(int));

    long long x = 4003600000000014;
    printf("Size of x: %li\n", sizeof(x));
    printf("Size of %s: %li\n", "float", sizeof(float));
}
