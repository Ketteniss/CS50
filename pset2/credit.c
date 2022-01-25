#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int ASCIItoD (int ASCII);   //  ASCII -> decimal (int)
int main (void) //  cc_num e.g. 4003600000000014
{
    printf("Please input credit card number: ");

    char buf[20];
    if ( fgets( buf, sizeof(buf), stdin ) != NULL )
    {
        // Remove new line
        char newline = '\10';
        for (int i = 0; buf[i]; i++)
        {
            if (buf[i] == newline)
            {
                buf[i] = '\0';
            }
        }

        // Initialize number string
        const char *cc_num = buf;

        // Check if all chars are numerals
        for (int i = 0; cc_num[i] != '\n'; i++)
        {
            // ASCII values for the numerals 0-9 => 48-57
            int cast = cc_num[i];
            if (cast < 48 || cast > 57)
            {
                printf("%s%c", "INVALID", '\n');
                return 1;
            }
        }

        //  Prepare company checks
        int first_dec = ASCIItoD(cc_num[0]);
        int second_dec = ASCIItoD(cc_num[1]);

        // Initialize company string, invalid by default
        char *cc_company = "INVALID";

        //  34, 37 (Amex), 4 (VISA), 51, 52, 53, 54, 55 (MASTERCARD)
        if ( first_dec >= 3 && first_dec <= 5)
        {
            // AMEX
            if (first_dec == 3)
            {
               if ( second_dec == 4 || second_dec == 7 )
               {
                   //  Assign valid value if ID correct
                   cc_company = "AMEX";
               }
            }

            // VISA
            else if ( first_dec == 4)
            {
                //  Assign valid value if ID correct
                cc_company = "VISA";
            }

            // MASTERCARD
            else if ( first_dec == 5)
            {
                if ( second_dec >= 1 && second_dec <= 5)
                {
                    //  Assign valid value if ID correct
                    cc_company = "MASTERCARD";
                }
            }
        }

        // Company verified
        if (strcmp(cc_company, "INVALID") != 0)
        {
            // Prepare 2nd verification under Luhn's algorithm
            int simple_sum = 0, product_sum = 0, numofdecs = strlen(cc_num);
            bool p_sum = false;

            //  Iterates backwards through every char in cc_num
            for (int i = numofdecs; i > 0; --i)
            {
                int decimal_value = ASCIItoD(cc_num[i]);

                if (p_sum)
                {
                    // Sum up the values of the digits of the products of the decimal times 2
                    product_sum += ( ( decimal_value * 2 ) % 10 ) + floor( ( decimal_value * 2.0 ) / 10 );
                    p_sum = false;
                }

                else
                {
                    // Simply sum up every decimal value
                    simple_sum += decimal_value;
                    p_sum = true;
                }
            }

            // Correct under Luhn
            if ((simple_sum + product_sum) % 10 == 0)
            {
                // Print validated company name
                printf("%s%c", cc_company, '\n');
            }

            // Incorrect under Luhn
            else
            {
                // Print invalidation
                printf("%s", "INVALID\n");  // not correct under Luhn
            }
        }

        // Not part of accepted group (AMEX, VISA, MASTERCARD)
        else
        {
            printf("%s", "INVALID\n");
            return 1;
        }
    }

}

//  ASCII into decimal transformations
int ASCIItoD (int ASCII) {
    int dec;
    switch (ASCII)
    {
    case '0':
        dec = 0;    //ASCII value: 48
        break;
    case '1':
        dec = 1;    //ASCII value: 49
        break;
    case '2':
        dec = 2;    //ASCII value: 50
        break;
    case '3':
        dec = 3;    //ASCII value: 51
        break;
    case '4':
        dec = 4;    //ASCII value: 52
        break;
    case '5':
        dec = 5;    //ASCII value: 53
        break;
    case '6':
        dec = 6;    //ASCII value: 54
        break;
    case '7':
        dec = 7;    //ASCII value: 55
        break;
    case '8':
        dec = 8;    //ASCII value: 56
        break;
    case '9':
        dec = 9;    //ASCII value: 57
        break;
    }
    return dec;
}