// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
//Node type structure for a character

typedef struct character
{
struct character* next;
char ch;
}character;

void writeList(character *character)
{
    while (character->next)
    {
        printf("%c", character->ch);
        character = character->next;
    }
    printf("%c\n", character->ch);
}

void freeList(character *character)
{
    if (character->next != NULL)
    {
        freeList(character->next);
    }
    free(character);
}

character** linkedListArr;

//Counts the number of words
int wordCount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Convert word to lowercase
    int n = strlen(word);
    char lowerCaseWord[n + 1];
    lowerCaseWord[n] = '\0';
    for (int i = 0; i < n; i++)
    {
        lowerCaseWord[i] = tolower(word[i]);
    }
    for (int i = 0; i < wordCount; i++)
    {
        int wordLength = 0;
        for (character* ptr = linkedListArr[i]; ptr != NULL; ptr = ptr->next)
        {
            wordLength++;
        }
        char tempWord[wordLength];
        int counter = 0;
        for (character* ptr = linkedListArr[i]; ptr != NULL; ptr = ptr->next)
        {
            tempWord[counter] = ptr->ch;
            ++counter;
        }
         if(strcmp(lowerCaseWord, tempWord) == 0)
        {
            //Return true if word matches the word in our dictionary
            return true;
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Pointer to read a file
    FILE * readPtr = fopen(dictionary,"r");
    char ch;
    int i = 0;
    //Checks if the File pointer is pointing to an existing file "small"
    if (readPtr)
    {
        while ((ch = fgetc(readPtr)) != EOF)
        {
            if (ch == '\n')
            {
                ++wordCount;
            }
        }
    }
    else
    {
        return false;
    }
    //Close and open the file again for reading
    fclose(readPtr);
    linkedListArr = malloc(sizeof(character *) * wordCount);
    if (linkedListArr == NULL)
    {
        return 1;
    }
    for (i = 0; i < wordCount; i++)
    {
        linkedListArr[i] = NULL;
    }
    i = 0;
    readPtr = fopen(dictionary,"r");
    while ((ch = fgetc(readPtr)) != EOF)
    {
        //Define a character pointer that points to allocated memory the size of a character struct node
        character* ptrToAllocatedChar = malloc(sizeof(character));
        //If the computer ran out of memory, free the allocated memory and end the program (Safety Check)
        if (ptrToAllocatedChar == NULL)
        {
            return 1;
        }
        //store ch into character node which is allocated
        ptrToAllocatedChar->ch = ch;
        ptrToAllocatedChar->next = NULL;
        if (linkedListArr[i])
        {
            for (character* ptr = linkedListArr[i]; ptr != NULL; ptr = ptr->next)
            {
                if (ptr->next == NULL)
                {
                    ptr->next = ptrToAllocatedChar;
                    //There is no Null terminator strings
                    //Look for \n to separate words
                    if (ptrToAllocatedChar->ch == '\n')
                    {
                        ptrToAllocatedChar->ch = '\0';
                        //free(ptrToAllocatedChar);
                        //ptr->next = NULL;
                        ++i;
                    }
                    break;
                }
            }
        }
        else
        {
            linkedListArr[i] = ptrToAllocatedChar;
        }
    }
    fclose(readPtr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (linkedListArr)
    {
        for (int i = 0; i < wordCount; i++)
        {
            freeList(linkedListArr[i]);
        }
        free(linkedListArr);
        return true;
    }
    else
    return false;
}
