// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool flag = false;
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    node *new_node;
    while (fscanf(file, "%s", word) != EOF)
    {
        unsigned int index = hash(word);
        if (hashtable[index] == NULL)
        {
            new_node = (node *) malloc(sizeof(node));
            if (new_node == NULL)
            {
                printf("Couldn't be created\n");
                return 1;
            }
            hashtable[index] = new_node;
            strcpy(hashtable[index] -> word, word);
            hashtable[index] -> next = NULL;
        }
        else
        {
            new_node = (node *) malloc(sizeof(node));
            if (new_node == NULL)
            {
                printf("Couldn't be created\n");
                return 1;
            }
            strcpy(new_node -> word, word);
            new_node -> next = hashtable[index] -> next;
            hashtable[index] -> next = new_node;
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    flag = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (flag == true)
    {
        int num_words = 0;
        node *temp, *crawler;

        for (int i = 0; i < N; i++)
        {
            if (hashtable[i] != NULL)
            {
                crawler = hashtable[i];
                while (crawler != NULL)
                {
                    temp = crawler -> next;
                    num_words++;
                    crawler = temp;
                }
            }
        }
        return num_words;
    }
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    node *crawler, *temp;

    if (hashtable[index] != NULL)
    {
        crawler = hashtable[index];
        while (crawler != NULL)
        {
            temp = crawler -> next;
            if (strcasecmp(crawler -> word, word) == 0)
            {
                return true;
            }
            crawler = temp;
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (flag == true)
    {
        node* temp;
        node* crawler;

        for(int n = 0; n < N; n++)
        {
            if (hashtable[n] != NULL)
            {
                // If only 1 node free it
                crawler = hashtable[n];
                while (crawler != NULL)
                {
                    temp = crawler->next;
                    free(crawler);
                    crawler = temp;

                }
                // free last node in list
                temp = crawler;
                free(temp);
            }
        }
        return true;
    }
    return false;
}
