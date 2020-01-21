# Questions

## What's `stdint.h`?

stdint.h is a header file used to define the exact width of integer data types by giving a set of typedefs.
Not every Processor in the world is the same, therefore the bit length of integer data types will vary on machines.
As a result, the purpose if stdint.h is to specifically define the bit length of integer data types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To specify the size of an integer and use it in that data type in a specific way. Using uint16_t means the integer has a size of 16 bits.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE is 1 byte
DWORD is 4 bytes
LONG is 4 bytes
WORD is 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

ASCII - BM

## What's the difference between `bfSize` and `biSize`?

bfSize is the amount of bytes for a file.
biSize is the amount of bytes for the BITMAPINFOHEADER also known as the info header.

## What does it mean if `biHeight` is negative?

The bitmap is a top-down DIB with the origin at the upper left corner when biHeight is negative.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If the file cannot be found after using fopen it will return NULL.

## Why is the third argument to `fread` always `1` in our code?

We only need to read one struct. By specifying 1 in our code, we will only read one struct.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

The padding will be 3, because 3 pixels * 3 bytes per pixel * 3 padding = 12.
12 is also a multiple of 4 so we will leave it at a padding of 3.

## What does `fseek` do?

Skips over padding to move to a specific location in a file.

## What is `SEEK_CUR`?

An integer constant, which when used, specifies that the offset is relative to the current file location.

## Whodunit?

It was Professor Plum with the candlestick in the library.
