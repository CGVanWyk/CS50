#include<cs50.h>
#include<stdio.h>
#include<string.h>
//To include usage of functions isupper, islower, and isalpha
#include <ctype.h>

int main(int argc, string argv[])
{
    //The length of the key word
    int keyLength;
    //Check whether there is only a single command-line argument passed when running ./vigenere
    if (argc != 2)
    {
        printf("The program only accepts a single command-line argument. Please re-run the program and insert a word as an argument\n");
        return 1;
    }
    keyLength = strlen(argv[1]);
    //Creates a key array using the length of the key received as command-line arguments
    int keyArray[keyLength];
    for (int j = 0; j < keyLength; j++)
    {
        //Checks whether the command-line argument received is alphabetical and prints an error otherwise and exits the program
        if (isalpha(argv[1][j]) == 0)
        {
            printf("You entered a non-alphabetic character as command-line argument. Please re-run and try again\n");
            return 1;
        }
        //Assigns every alphabetical letter an integer value in the keyArray
        //Building the key that needs to be used
        if (argv[1][j] == 'A' || argv[1][j] == 'a')
        {
            keyArray[j] = 0;
        }
        else if (argv[1][j] == 'B' || argv[1][j] == 'b')
        {
            keyArray[j] = 1;
        }
        else if (argv[1][j] == 'C' || argv[1][j] == 'c')
        {
            keyArray[j] = 2;
        }
        else if (argv[1][j] == 'D' || argv[1][j] == 'd')
        {
            keyArray[j] = 3;
        }
        else if (argv[1][j] == 'E' || argv[1][j] == 'e')
        {
            keyArray[j] = 4;
        }
        else if (argv[1][j] == 'F' || argv[1][j] == 'f')
        {
            keyArray[j] = 5;
        }
        else if (argv[1][j] == 'G' || argv[1][j] == 'g')
        {
            keyArray[j] = 6;
        }
        else if (argv[1][j] == 'H' || argv[1][j] == 'h')
        {
            keyArray[j] = 7;
        }
        else if (argv[1][j] == 'I' || argv[1][j] == 'i')
        {
            keyArray[j] = 8;
        }
        else if (argv[1][j] == 'J' || argv[1][j] == 'j')
        {
            keyArray[j] = 9;
        }
        else if (argv[1][j] == 'K' || argv[1][j] == 'k')
        {
            keyArray[j] = 10;
        }
        else if (argv[1][j] == 'L' || argv[1][j] == 'l')
        {
            keyArray[j] = 11;
        }
        else if (argv[1][j] == 'M' || argv[1][j] == 'm')
        {
            keyArray[j] = 12;
        }
        else if (argv[1][j] == 'N' || argv[1][j] == 'n')
        {
            keyArray[j] = 13;
        }
        else if (argv[1][j] == 'O' || argv[1][j] == 'o')
        {
            keyArray[j] = 14;
        }
        else if (argv[1][j] == 'P' || argv[1][j] == 'p')
        {
            keyArray[j] = 15;
        }
        else if (argv[1][j] == 'Q' || argv[1][j] == 'q')
        {
            keyArray[j] = 16;
        }
        else if (argv[1][j] == 'R' || argv[1][j] == 'r')
        {
            keyArray[j] = 17;
        }
        else if (argv[1][j] == 'S' || argv[1][j] == 's')
        {
            keyArray[j] = 18;
        }
        else if (argv[1][j] == 'T' || argv[1][j] == 't')
        {
            keyArray[j] = 19;
        }
        else if (argv[1][j] == 'U' || argv[1][j] == 'u')
        {
            keyArray[j] = 20;
        }
        else if (argv[1][j] == 'V' || argv[1][j] == 'v')
        {
            keyArray[j] = 21;
        }
        else if (argv[1][j] == 'W' || argv[1][j] == 'w')
        {
            keyArray[j] = 22;
        }
        else if (argv[1][j] == 'X' || argv[1][j] == 'x')
        {
            keyArray[j] = 23;
        }
        else if (argv[1][j] == 'Y' || argv[1][j] == 'y')
        {
            keyArray[j] = 24;
        }
        else if (argv[1][j] == 'Z' || argv[1][j] == 'z')
        {
            keyArray[j] = 25;
        }
    }
    //Received unencrypted text from the user
    string plaintext = get_string("plaintext:  ");
    //Get the length of the string
    int length = strlen(plaintext);
    //Creates a counter that needs to be used for the keyArray
    int keyCounter = 0;
    //Shifting the plaintext to encrypt it for ciphertext
    for (int i = 0; i < length; i++)
    {
        //Check whether the character is lower or uppercase first
        if (islower(plaintext[i]))
        {
            //When the Decimal ASCII value reaches a certain point it overflows and turns negative, giving all sorts of problems
            //Make the value lower and do all the necessary calculations and then add the value you subtracted at the end of the if statement
            plaintext[i] -= 96;
            /*  The keyArray length is usually smaller than the length of the plaintext received from the user.
                The if statement and keyCounter is needed in order for the keyArray to go back to the beginning of the array and not go out of bounds.
            */
            if (keyCounter >= keyLength)
            {
                keyCounter = 0;
                //Encrypts the plaintext to ciphertext by adding each character of the plaintext to the corresponding key character
                plaintext[i] += keyArray[keyCounter];
                keyCounter++;
            }
            else
            {
                //Encrypts the plaintext to ciphertext by adding each character of the plaintext to the corresponding key character
                plaintext[i] += keyArray[keyCounter];
                keyCounter++;
            }
            if (plaintext[i] > 26)
            {
                plaintext[i] -= 26;
            }
            plaintext[i] += 96;
        }
        else if (isupper(plaintext[i]))
        {
            //Uppercase characters don't have the overflow problem lower case characters has
            if (keyCounter >= keyLength)
            {
                keyCounter = 0;
                //Encrypts the plaintext to ciphertext by adding each character of the plaintext to the corresponding key character
                plaintext[i] += keyArray[keyCounter];
                keyCounter++;
            }
            else
            {
                //Encrypts the plaintext to ciphertext by adding each character of the plaintext to the corresponding key character
                plaintext[i] += keyArray[keyCounter];
                keyCounter++;
            }
            if (plaintext[i] > 90)
            {
                plaintext[i] -= 26;
            }
        }
    }
    //Output Ciphertext for the user
    printf("ciphertext: %s\n", plaintext);
}
