#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //MARIO PYRAMID SCHEME >:ß

    // To create our pyramids we are going to contruct
    // a matrix filled with hash-symbols or white-spaces

    // First we prompt the user for the pyramid height, then
    // we intitalise our variables for the needed matrix dimensions

    int numbOfRows;
    do
    {
        numbOfRows = get_int("Please input desired pyramid height: ");
    } while (numbOfRows < 1 || numbOfRows > 8);

    int numbOfCollumns = numbOfRows * 2 + 2;

    for (int i = 0; i < numbOfRows; i++)    // outer loop for matrix rows
    {
        for (int j = 0; j < numbOfCollumns; j++)  // inner loop for matrix collumns
        {
            if (j <= numbOfRows - 1)    // to the left of the hole
            {
                if (j >= (numbOfRows - 1) - i)  // left sided pyramid spaces
                {
                    printf("#");
                } else {            // empty space around left sided pyramid
                    printf(" ");
                }
            }
            if(j >= numbOfRows + 2)   // to the right of the hole
            {
                if (j - i <= numbOfCollumns - numbOfRows) // right sided pyramid spaces
                {
                   printf("#");
                } else {            // empty space around right sided pyramid
                    printf(" ");
                }
            }
            if (j >= numbOfRows && j < numbOfRows + 2)
            {
                printf(" ");        // hole in the middle
            }
        }
        printf("\n");
    }

}