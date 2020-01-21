// Helper functions for music
#include <string.h>
#include <math.h>
#include <cs50.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    if (fraction[2] == '2')
    {
        //Converts char to int and subtracts 48 to make it the correct integer values
        //multiplication is to make the decimal value eighths
        return ((int)fraction[0] - 48) * 4;
    }
    else if (fraction[2] == '4')
    {
        return ((int)fraction[0] - 48) * 2;
    }
    else if (fraction[2] == '8')
    {
        return fraction[0] - 48;
    }
    return fraction[0];
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    //Store the difference between the ocateves in an integer
    int octaveDiff = 0;
    //Default frequency of A4 is 440
    double frequency = 440;
    double distanceFromA = 0;
    //Tests whether the input string is A4 and returns the default frequency if true
    if (strcmp(note, "A4") == 0)
    {
        return frequency;
    }
    else
    {
        //Calculates the octave Difference and stores it in octaveDiff
        if (strlen(note) == 2)
        {
            octaveDiff = ((int)note[1] - 48) - 4;
        }
        else if (strlen(note) == 3)
        {
            octaveDiff = ((int)note[2] - 48) - 4;
        }
        //Octave Difference cannot be negative, therefore multiply negative differences with -1
        if (octaveDiff < 0)
        {
            octaveDiff *= -1;
            //If it is negative then the direction of the Note from A4 is on the leftside of A4. Therefore you need to divide the frequency
            //Division of 2 is part of the formula for calculating the frequency of a note
            for (int i = 0; i < octaveDiff; i++)
            {
                frequency = frequency / 2;
            }
        }
        else
        {
            //If the octaveDiff is positive then the Note is on the rightside of A4 and therefore you need to multiply by 2
            for (int i = 0; i < octaveDiff; i++)
            {
                frequency = frequency * 2;
            }
        }
        //Compensate for # and b. Multiplication and Division is part of the formula for calculating the frequency of the Note
        if (note[1] == '#')
        {
            frequency = frequency * pow(2.00, 1.00 / 12.00);
        }
        else if (note[1] == 'b')
        {
            frequency = frequency / pow(2.00, 1.00 / 12.00);
        }
        //Compensate for any Note. Every note has a certain distance from A
        //The Distance is also equal to the amount of semitones from A
        if (note[0] == 'C')
        {
            distanceFromA = 9;
        }
        else if (note[0] == 'D')
        {
            distanceFromA = 7;
        }
        else if (note[0] == 'E')
        {
            distanceFromA = 5;
        }
        else if (note[0] == 'F')
        {
            distanceFromA = 4;
        }
        else if (note[0] == 'G')
        {
            distanceFromA = 2;
        }
        else if (note[0] == 'B')
        {
            distanceFromA = 2;
            frequency = frequency * pow(2.00, distanceFromA / 12.00);
            return round(frequency);
        }
        frequency = frequency / pow(2.00, distanceFromA / 12.00);
    }
    return round(frequency);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    //If the user inputs nothing then it is equal to "" and therefore represents a rest
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
