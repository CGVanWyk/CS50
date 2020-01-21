#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <math.h>

int main(int argc, char *argv[])
{
    //Checks if correct command-line arguments have been passed to main
    if (argc != 2)
    {
        fprintf(stderr, "Please Enter a filename to open.\n");
        return 1;
    }
    //Open input file
    FILE *file = fopen(argv[1], "r");
    //Checks if the file is opened correctly
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }
    FILE * image = NULL;
    char imageArray[50];
    unsigned char buffer[512];
    //Cleans all elements in the buffer before reading
    for (int i = 0; i < 512;i++)
    {
        buffer[i] = 0x0;
    }
    //Boolean variable used to check if an image has been found
    bool isFound = false;
    int counter = 0;
    //While not at the end of the file
    while(!feof(file))
    {
        //If fread reads the end of the file, break the while loop
        if (fread(buffer, 1, 512, file) == 0)
        {
            break;
        }
        else
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
            {
                if (isFound == true)
                {
                    fclose(image);
                }
                else
                {
                    isFound = true;
                }
                sprintf(imageArray, "%03i.jpg", counter);
                image = fopen(imageArray, "w");
                ++counter;
            }
            if (isFound == true)
            {
                //Write image to file
                fwrite(&buffer,512, 1, image);
            }
        }
    }
    fclose(file);
    fclose(image);
    return 0;
}