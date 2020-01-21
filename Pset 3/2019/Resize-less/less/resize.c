// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include "bmp.h"
#include <math.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize factor infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    //Initialize the factor by which the image needs to be resized
    int n = atoi(argv[1]);

    //Check if the user inputs a factor between 1-100
    if (n <= 0 || n > 100)
    {
        printf("Factor needs to be between 1-100\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_resized;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_resized = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_resized;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_resized = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //Resize Width and Height
    bi_resized.biWidth  *= n;
    bi_resized.biHeight *= n;

    //Calculate padding
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) %4) % 4;
    //Calculate resized padding
    int resizedPadding = (4 - (bi_resized.biWidth * sizeof(RGBTRIPLE)) %4) % 4;
    // Calculate size of Bitmap File Header
    bf_resized.bfSize = 54 + bi_resized.biWidth * abs(bi_resized.biHeight) * 3 + abs(bi_resized.biHeight) *  resizedPadding;
    // Calculate size of Bitmap info header
    bi_resized.biSizeImage = ((((bi_resized.biWidth * bi_resized.biBitCount) + 31) & ~31) / 8) * abs(bi_resized.biHeight);
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_resized, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_resized, sizeof(BITMAPINFOHEADER), 1, outptr);
    RGBTRIPLE triple;
    RGBTRIPLE scanLine[bi_resized.biWidth];
    int pixel = 0;
    int counter = 0;
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //Start at the line's first pixel
        pixel = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // read pixel from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            //Repeat the pixel n times to scale horizontally and store it in scanLine array
            counter = 0;
            while (counter < n)
            {
                scanLine[pixel] = triple;
                ++pixel;
                ++counter;
            }
        }
        // Skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
        //Print the array horizontally with the padding into the output file pointer
        for (int j = 0; j < n; j++)
        {
            fwrite(scanLine, sizeof(RGBTRIPLE), bi_resized.biWidth,outptr);
            // Add a new padding
            for (int l = 0; l < resizedPadding; l++)
            fputc(0x00, outptr);
        }
    }
    // close infile
    fclose(inptr);
    // close outfile
    fclose(outptr);
    return 0;
}