// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26 * 'z';

// Hash table
int word_count = 0;
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int i = hash(word);

    node *temp = table[i];
    node *cursor = table[i];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    /* Sources
        http://oeis.org/wiki/Higher-order_prime_numbers#:~:text=%7B2%2C%203%2C%205%2C,%2C%20157%2C%20...%7D for a large prime number
        https://www.cs.cornell.edu/courses/cs312/2008sp/lectures/lec21.html#:~:text=With%20modular%20hashing%2C%20the%20hash,lowest%2Dorder%20bits%20of%20k.
        http://www.cse.yorku.ca/~oz/hash.html
    */

    unsigned long hash = 33967;
    int c;
    while ((c = *word++))
    {
        hash = ((hash << 10) + hash) + tolower(c);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the file
    FILE *file = fopen(dictionary, "r");

    if (!file)
    {
        return false;
    }

    // Max length of word is defined in dictionary.h
    char word[LENGTH + 1];

    // Check each word while it is not at the end of the file
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        // Check if it successfully allocated the memory
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        n->next = NULL;

        // Get the index
        int i = hash(word);

        if (table[i] == NULL)
        {
            table[i] = n;
        }
        else
        {
            n->next = table[i];
            table[i] = n;
        }

        word_count++;
    }

    fclose(file);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *temp = head;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }

    return true;
}
