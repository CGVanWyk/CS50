#include<cs50.h>
#include<stdio.h>
#include<string.h>
//To include usage of functions isupper and islower
#include <ctype.h>

int main(int argc, string argv[])
{
    //Check whether there is only a single command-line argument passed when running ./caesar
    if (argc != 2)
    {
        printf("The program only accepts a single command-line argument. Please re-run the program and insert a non-negative integer as an argument\n");
        return 1;
    }
    //Converts the key from a string to int
    int key = atoi(argv[1]);
    //The key must not be higher than 26 in order for the shift to correctly occur, hence the magical number 26 which is the number of letters in the alphabet
    if (key >= 26)
    {
        key %= 26;
    }
    //Received unencrypted text from the user
    string plaintext = get_string("plaintext:  ");
    //Get the length of the string
    int length = strlen(plaintext);
    //Shifting the plaintext to encrypt it for ciphertext
    for (int i = 0; i < length; i++)
    {
        //Check whether the character is lower or uppercase first
        if (islower(plaintext[i]))
        {
            //When the Decimal ASCII value reaches a certain point it overflows and turns negative, giving all sorts of problems
            //Make the value lower and do all the necessary calculations and then add the value you subtracted at the end of the if statement
            plaintext[i] -= 96;
            plaintext[i] += key;
            if (plaintext[i] > 26)
            {
                plaintext[i] -= 26;
            }
            plaintext[i] += 96;
        }
        else if (isupper(plaintext[i]))
        {
            //Uppercase characters don't have the overflow problem lower case characters has
            plaintext[i] += key;
            if (plaintext[i] > 90)
            {
                plaintext[i] -= 26;
            }
        }
    }
    //Output Ciphertext for the user
    printf("ciphertext: %s\n", plaintext);
}