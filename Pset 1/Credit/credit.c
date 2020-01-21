#include<cs50.h>
#include<stdio.h>
#include<string.h>

int main(void)
{
    //User Input Credit Card Number and is stored as a string
    string inputCreditcard;
    //Used to store the length of the card
    int cardLength = 0;
    //The sum of the second-to-last digit to the beginning of the array multiplied by two
    int sumMathArray = 0;
    //The sum of the other digits that is not in the previous array
    int sumOther = 0;
    //The sum of sumMathArray and sumOther
    int sumTotal = 0;
    //To check if the card is valid. If the value is 0 it means the card is valid
    int isLegitCard = 0;
    //Check whether the user inputs a numeric value or any other invalid character
    bool isNumeric = 0;
    //The loop is used to keep asking the user for a numeric value if they typed in a non-numeric character
    do
    {
        inputCreditcard = get_string("Number: ");
        cardLength = strlen(inputCreditcard);
        for (int i = 0; i < cardLength; i++)
        {
            if (inputCreditcard[i] >= 48 && inputCreditcard[i] <= 57)
            {
                isNumeric = 1;
            }
            else
            {
                isNumeric = 0;
                break;
            }
        }
    }
    while (isNumeric != 1);
    //Declare an integer array with the same length as the credit card the user typed in
    int creditCard[cardLength];
    //Declare an integer array same as the above array but the array is longer by one. This is to avoid going out of bounds with the array
    //The array is used to do all the mathematical calculations and store newer values in the array, without losing the original array values which is still stored in the creditCard array
    int mathArray[(cardLength + 1)];
    //This loop is used to transfer the values from the string array to the integer arrays to do mathematical calculations
    for (int i = 0; i < cardLength; i++)
    {
        //Static casting the string values to integer values
        //You minus the newer converted value by 48, because characters is stored with different ASCII values
        creditCard[i] = (int)inputCreditcard[i] - 48;
        //Assigns values duplicate from the arrays creditCard to mathArray
        mathArray[i] = creditCard[i];
    }
    //The last value of mathArray is assigned 0 because mathArray is longer than the creditCard array
    mathArray[cardLength] = 0;
    //The sum of the second-to-last digit to the beginning of the array multiplied by two
    for (int i = (cardLength - 2); i >= 0; i -= 2)
    {
        mathArray[i] *= 2;
        if (mathArray[i] >= 10)
        {
            mathArray[(i + 1)] = mathArray[i] - 10;
            mathArray[i] = 1;
            sumMathArray = sumMathArray + mathArray[i] + mathArray[(i + 1)];
        }
        else
        {
            sumMathArray = sumMathArray + mathArray[i];
        }
    }
    //The sum of the other digits that is not in the previous array
    for (int i = (cardLength - 1) ; i >= 0; i -= 2)
    {
        sumOther = sumOther + creditCard[i];
    }
    //The sum of sumMathArray and sumOther
    sumTotal = sumMathArray + sumOther;
    //Validate the creditcard using modulus operator
    isLegitCard = sumTotal % 10;
    //Outputs on the screen to the user the type of credit card or if the credit card is invalid
    if (isLegitCard == 0)
    {
        if ((creditCard[0] == 3 && (creditCard[1] == 4 || creditCard[1] == 7)) && cardLength == 15)
        {
            printf("AMEX\n");
        }
        else if ((creditCard[0] == 5 && (creditCard[1] == 1 || creditCard[1] == 2 || creditCard[1] == 3 || creditCard[1] == 4
                                         || creditCard[1] == 5)) && cardLength == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (creditCard[0] == 4 && (cardLength == 13 || cardLength == 16))
        {
            printf("VISA\n") ;
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}