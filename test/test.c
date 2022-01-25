#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 45
#define DICTIONARY "dictionaries/large"

typedef struct node
{
    char first;
    char second;
    int count;
}
node;

// char *dic
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }
    node *word_count = malloc((2*sizeof(char) + sizeof(int)) * (676));
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            word_count[26*i + j].first = 97 + i;
            word_count[26*i + j].second = 97 + j;
            word_count[26*i + j].count = 0;
        }
    }


    FILE *dictionary = fopen(argv[1], "r");
    if (dictionary == NULL)
    {
        fclose(dictionary);
        return 1;
    }
    char word[LENGTH+1];
    int index = 0;
    char c;
    while (fread(&c, sizeof(char), 1, dictionary))
    {
        word[index] = c;
        index++;

        if (c == '\n')
        {
            for (int i = 0; i < (26*26); i++)
            {
                if (word_count[i].first == word[0] && word_count[i].second == word[1])
                {
                    word_count[i].count += 1;
                }
            }
            index = 0;
        }
    }
    for (int i = 0; i < (26*26); i++)
    {
        printf("%c%c: %d times\n", word_count[i].first, word_count[i].second,  word_count[i].count);
    }
    free(word_count);
    fclose(dictionary);
    printf("\n");
}