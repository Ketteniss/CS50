#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int ASCIItoD (int ASCII);   //  ASCII -> decimal (int)
int main (void) //  cc_num e.g. 4003600000000014
{
    printf("Please input credit card number: ");

    char buf[20];
    if ( fgets( buf, sizeof(buf), stdin ) != NULL )
    {
        const char *cc_num = buf;   //  lets go!

        //  check if company ID is accepted
        int first_dec = ASCIItoD( cc_num[0] );
        int second_dec = ASCIItoD( cc_num[1] );

        //  I'd prefer to contruct cc_company as an empty string and then simply assign
        //  if it's validated an accepted company name string to it. But since this is 
        //  above my capabilities at the moment I will instead assign each company a 
        //  char value and infer the according answer string later through that 

        char cc_company = '\0';     // invalid by default
        if ( first_dec >= 3 || first_dec <= 5)  //  AMEX_ID: 34, 37; VISA_ID: 4; MASTERCARD_ID: 51-55
        {
            if (first_dec == 3)     
            {
               if ( second_dec == 4 || second_dec == 7 ) 
               {
                   cc_company = 'A';    //  assign valid value if ID correct
               }
            } 
            else if ( first_dec == 4) 
            {
                cc_company = 'V';   //  assign valid value if ID correct
            } 
            else if ( first_dec == 5) 
            {
                if ( second_dec >= 1 && second_dec <= 5)
                {
                    cc_company = 'M';   //  assign valid value if ID correct
                }
            }
        }
        if ( cc_company == '\0' )
        {
            printf("%s\n", "INVALID");
        } 
        else 
        {
            //  Let's see if number still conform under Luhn's algorithm 
            int simple_sum = 0, product_sum = 0, step = 0;     
            int numofdec = strlen( cc_num ) - 1; 
            for ( int i = numofdec - 1; i >= 0; --i ) //  iterates backwards through every char in cc_num
            {
                int decimal_value = ASCIItoD( cc_num[i] );

                if ( step == 1)     // 1 := sum up values of digits of products
                {
                    product_sum += ( ( decimal_value * 2 ) % 10 ) + floor( ( decimal_value * 2.0 ) / 10 );
                    step = 0;
                } else {            // 0 := simply sum up decimal_value
                    simple_sum += decimal_value;
                    step = 1;
                }
            }
            if ( ( simple_sum + product_sum ) % 10 == 0 )   // correct under Luhn
            {
                if ( cc_company == 'A' ) 
                {
                    printf("%s\n", "AMEX");
                }    
                if ( cc_company == 'V' ) 
                {
                    printf("%s\n", "VISA");
                }
                if ( cc_company == 'M' ) 
                {
                    printf("%s\n", "MASTERCARD");
                }
            } 
            else 
            {
                printf("%s\n", "INVALID");  // not correct under Luhn
            }
        }
    }
    
}

//  ASCII into decimal transformations
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