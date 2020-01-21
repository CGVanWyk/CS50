#include<cs50.h>
#include<stdio.h>
//Mario, more comfortable
int main(void)
{
    //Variables initialized essential for pyramid later
    int hashCount = 1;
    int height = -1;
    //Input Height of pyramid from user
    do
    {
        printf("Height: ");
        height = get_int();
    }
    while (height < 0 || height > 23);
    //variable initialized needed to print spaces for pyramid
    int spaceCount = (height - 1);
    //Printing half-pyramids for Mario
    for (int i = 0; i < height; i++)
    {
        for (int j = spaceCount; j > 0; j--)
        {
            printf(" ");
        }
        for (int j = hashCount; j > 0; j--)
        {
            printf("#");
        }
        printf("  ");
        for (int j = hashCount; j > 0; j--)
        {
            printf("#");
        }
        printf("\n");
        --spaceCount;
        ++hashCount;
    }
}