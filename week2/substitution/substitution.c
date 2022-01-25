#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main( int argc, const char *argv[] ) 
{
    if ( argc - 1 == 1 )  // 1 Argument: Cipher-Schlüssel (26 Zeichen) 
    {
        const char *key = argv[1];

        //**VALIDATE KEY**
        if ( strlen(key) != 26 ) 
        {   
            printf("Not 26");
            return 1;
        }    // if key cant map onto alphabet: fail
        else
        {
            for ( int i = 0; i < strlen(key); i++)  //  check fail case  >>   
            {
                if ( !islower( key[i] ) && !isupper( key[i] ) ) 
                {
                    printf("not alphabethical");
                    return 1;   // if not alphabethical: fail
                }
            }
            for ( int i = 0; i < strlen(key); i++ )  //  check fail case  >>         
            {
                for ( int j = i + 1; j < strlen(key); j++ )  
                {
                    if ( key[i] == key[j] ) 
                    {
                        printf("letter twice: %c\n", key[j]);
                        return 1;   //  if letter twice: fail
                    }
                }
            }
        }
        //**DONE******************
        //**KEY CONSIDERED VALID**

        //              abcdefghijklmnopqrstuvwxyz                                                                                
        printf("plaintext: ");
        char buf[100];
        if ( fgets( buf, sizeof(buf), stdin ) != NULL )
        {
            printf("\nciphertext: ");
            const char *plaintext = buf;
            for ( int i = 0; i < strlen( plaintext ); i++ )
            {
                if ( isupper( plaintext[i] ) ) //  plaintext-char is uppercase letter
                {
                    if ( isupper( key[plaintext[i] - 65] ) )   //  key is uppercase: 
                    {
                        printf( "%c", key[plaintext[i] - 65] );  //  just print
                    }      
                    else    //  key is lowercase: 
                    {
                        printf( "%c", key[plaintext[i] - 65] - 32 ); //  make uppercase
                    }
                }
                else if ( islower( plaintext[i]) )  //  plaintext-char is lowercase letter
                {
                    if ( islower( key[ plaintext[i] - 97 ] ) )   //  if key also lowercase: 
                    {
                        printf( "%c", key[ plaintext[i] - 97 ] );  //  just print
                    }
                    else    //  key is uppercase: 
                    {
                        printf( "%c", key[plaintext[i] - 97] + 32 );  //  make lowercase
                    }
                }
                else    // plaintext-char is not a letter
                {
                    printf("%c", plaintext[i]);  //  just print
                }
            }  
        }
        printf("\n");
        return 0;
    } 
    else if ( argc == 1 )  // Kein Key eingegeben 
    {
        printf("Kein Key eingegeben");
        return 1;
    } 
    else  // Zu viele Argumente 
    {
        printf("Zu viele Argumente");
        return 1;
    }
}