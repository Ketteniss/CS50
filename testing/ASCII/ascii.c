#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
    printf("%c:%d ", 'a', 'a');
    printf("%c:%d ", 'z', 'z');

    printf("%c:%d ", 'A', 'A');
    printf("%c:%d \n", 'Z', 'Z');
    for(int i = 65; i <= 90; i++) printf("%d:%d ", i-64, i);

}