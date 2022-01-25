// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table: first two letters -> 26*26
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Find hash key for the word that we are checking for
    int key = hash(word);

    // Make lowercase
    char compare_str[LENGTH + 1];
    strcpy(compare_str, word);
    for (int i = 0; compare_str[i]; i++)
    {
        compare_str[i] = tolower(compare_str[i]);
    }

    // Search chained list of nodes within table[key]
    for (node *tmp = table[key]; tmp != NULL; tmp = tmp->next)
    {
        if ( strcmp(tmp->word, compare_str) == 0 )
        {
            return true;
        }
    }
    return false;
}

// djb2 by Dan Bernstein
unsigned int hash(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while (( c = tolower((*str++)) ))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Prepare hash table
    for(int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open dictionary file to be loaded
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        char *errormsg = "dict -> NULL";
        printf("%s", errormsg);
        return false;
    }

    // Prepare looping word for word
    char word[LENGTH+1];
    char c;
    int i = 0;

    // Fill up hash table with words from dictionary
    while (fread(&c, sizeof(char), 1, dict))
    {
        // If word continues
        if (c != '\n')
        {
            // Add read letter
            word[i] = c;

            // Continue with next letter
            i++;
        }

        // If word done
        else
        {
            // Finish string with '\0'
            word[i] = '\0';

            // Find key for hash table
            int key = hash(word);

            // Prepare new node
            node *neu = malloc(sizeof(node));
            if  (neu == NULL)
            {
                return false;
            }
            strcpy(neu->word, word);
            neu->next = NULL;

            // Add node to table if still empty
            if (table[key] == NULL)
            {
                table[key] = neu;
            }

            // Otherwhise insert node
            else
            {
                neu->next = table[key];
                table[key] = neu;
            }

            // Prepare for next word
            i = 0;
        }
    }

    // Close dictionary file because dictionary loaded
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Prepare to count
    int count = 0;

    // Iterate through hash table
    for (int i = 0; i < N; i++)
    {
        // Iterate all nodes of linked lists found
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            // Count each node
            count ++;
        }
    }

    // Return word count
    return count;

    /*  More efficient implementation of size() within the load function just returns global count variable
        seen here : https://collinsnote.com/cs50-speller-solution-2020-my-explanation/
        by Collin */
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through hash table
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
