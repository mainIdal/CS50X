#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize factor infile outfile\n");
        return 1;
    }

    // remember arguments
    int factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input & output files
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    if ((factor <= 0) || (factor > 100))
    {
        fprintf(stderr, "Factor must be in 1 - 100 range\n");
        return 1;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    BITMAPFILEHEADER bfo = bf;
    BITMAPINFOHEADER bio = bi;

    if (factor == 1)
    {
        bfo = bf;
        bio = bi;
    }
    else
    {
        bfo = bf;
        bio = bi;

        bio.biWidth = bi.biWidth * factor;
        bio.biHeight = bi.biHeight * factor;
        int padding =  (4 - (bio.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        bio.biSizeImage = (bio.biWidth * abs(bio.biHeight) * 3) + (padding * bio.biWidth);
        bfo.bfSize = bio.biSizeImage + 54;
    }


    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 1;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfo, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bio, sizeof(BITMAPINFOHEADER), 1, outptr);

    // if factor == 1 just copy file
    if (factor == 1)
    {
        // determine padding for scanlines
        int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
                fputc(0x00, outptr);
        }
        fclose(inptr);
        fclose(outptr);
        return 0;
    }
    else
    {
        int paddingIn =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        int paddingOut =  (4 - (bio.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            RGBTRIPLE* buffer = malloc(bi.biWidth * sizeof(RGBTRIPLE));
            RGBTRIPLE temp;
            
            for (int j = 0; j < bi.biWidth; j++)
            {
                fread(&temp, sizeof(RGBTRIPLE), 1, inptr);
                buffer[j] = temp;
            }
            
            for (int k = 0; k < factor; k++)
            {
                int iterator = 0;
                
                for (int l = 0; l < bi.biWidth; l++)
                {
                    for(int m = 0; m < factor; m++)
                    {
                        fwrite(&buffer[iterator], sizeof(RGBTRIPLE), 1, outptr);
                    }
                    
                    iterator += 1 % bi.biWidth;
                }
                
                for (int bar = 0; bar < paddingOut; bar++)
                    fputc(0x00, outptr);
             }
                
            fseek(inptr, paddingIn, SEEK_CUR);    
            free(buffer);
        }
    }


    fclose(inptr);
    fclose(outptr);
    return 0;
}