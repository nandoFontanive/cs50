// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

int loaded_words = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash the word to obtain its hash value

    int hash_value = hash(word);
    node *cursor = table[hash_value];

    while (cursor != NULL)
    {
        // access linked list at the index in the hash table
        if (strcasecmp(word, cursor->word) == 0)
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
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    // Read each word in the file one at a time
    char word[LENGTH + 1];

    while (fscanf(source, "%s", word) != EOF)
    {
        // Create space for a new hash table node
        node *n = malloc(sizeof(node));
        node *cursor = NULL;
        if (n == NULL)
        {
            fclose(source);
            return false;
        }
        // Copy the word into the new node
        strcpy(n->word, word);

        // Hash the word to obtain its hash value
        int hashed = hash(word);

        n->next = table[hashed];
        table[hashed] = n;
        loaded_words++;

    }
    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (loaded_words != 0)
    {
        return loaded_words;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
