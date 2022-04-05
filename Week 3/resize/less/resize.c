// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
    int n = atoi(argv[1]);
    if(n <= 0 || n > 100)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    BITMAPFILEHEADER bf, bfo;
    BITMAPINFOHEADER bi, bio;

    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    bfo = bf;
    bio = bi;

    bio.biWidth = bi.biWidth * n;
    bio.biHeight = bi.biHeight * n;
    int padding =  (4 - (bio.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bio.biSizeImage = (bio.biWidth * abs(bio.biHeight) * 3) + (padding * bio.biWidth);
    bfo.bfSize = bio.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfo, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bio, sizeof(BITMAPINFOHEADER), 1, outptr);

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

            for (int k = 0; k < bi.biWidth; k++)
                for (int l = 0; l < n; l++)
                    fwrite(&buffer[k], sizeof(RGBTRIPLE), 1, outptr);

            for (int k = 0; k < paddingOut; k++)
                fputc(0x00, outptr);

            fseek(inptr, paddingIn, SEEK_CUR);
            free(buffer);
        }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
