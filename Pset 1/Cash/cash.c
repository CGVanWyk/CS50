#include<cs50.h>
#include<stdio.h>
//Use math.h to use round function
#include<math.h>
int main(void)
{
    float cash = 0;
    int counter = 0;
    int iCash = 0;
    //Test if the user inserted a non-negative number correctly
    do
    {
        //Converts Dollar to Cents and rounds the amount for correctness
        cash = round(get_float("Change owed: ") * 100);
        //Convert float to int to store everything correctly in memory
        iCash = (int)cash;
    }
    while (iCash < 0);
    //Get the Greedy Change using conditions
    //The While Loop checks that the amount isn't 0
    while (iCash > 0)
    {
        if (iCash >= 25)
        {
            while (iCash >= 25)
            {
                iCash -= 25;
                ++counter;
            }

        }
        if (iCash >= 10)
        {
            while (iCash >= 10)
            {
                iCash -= 10;
                ++counter;
            }
        }
        if (iCash >= 5)
        {
            while (iCash >= 5)
            {
                iCash -= 5;
                ++counter;
            }
        }
        if (iCash >= 1)
        {
            while (iCash >= 1)
            {
                iCash -= 1;
                ++counter;
            }
        }
    }
    //Print out the minimum amount of coins required to give the user change
    printf("%i\n", counter);
}