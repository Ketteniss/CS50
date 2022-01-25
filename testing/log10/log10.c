#include <stdio.h>
#include <math.h>

int ASCIItoD (int ASCII);
int main(void)
{
    double x = log10(2);
     printf("%lf", x);
}
//ASCII Decimal Numbers Transformations
int ASCIItoD (int ASCII) {
    int dec;
    switch (ASCII)
    {
    case '0':
        dec = 0;
        break;
    case '1':
        dec = 1;
        break;
    case '2':
        dec = 2;
        break;
    case '3':
        dec = 3;
        break;
    case '4':
        dec = 4;
        break;
    case '5':
        dec = 5;
        break;
    case '6':
        dec = 6;
        break;
    case '7':
        dec = 7;
        break;
    case '8':
        dec = 8;
        break;
    case '9':
        dec = 9;
        break;
    default:
        break;
    }
    //ASCII value: '48'        display character: '0'
    //ASCII value: '49'        display character: '1'
    //ASCII value: '50'        display character: '2'
    //ASCII value: '51'        display character: '3'
    //ASCII value: '52'        display character: '4'
    //ASCII value: '53'        display character: '5'
    //ASCII value: '54'        display character: '6'
    //ASCII value: '55'        display character: '7'
    //ASCII value: '56'        display character: '8'
    //ASCII value: '57'        display character: '9'
    return dec;
}