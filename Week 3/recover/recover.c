#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t byte;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "File could not open to read\n");
        return 2;
    }

    byte* buffer = malloc(512);
    int file_num = 0;
    char file_name[9];
    int end_file;

    while (fread(buffer, 1, 512, file) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(file_name, "%03d%s", file_num, ".jpg");
            FILE* image = fopen(file_name, "w");
            if (image == NULL)
            {
                fprintf(stderr, "File could not open to write\n");
                return 2;
            }
            fwrite(buffer, 1, 512, image);
            if (fread(buffer, 1, 512, file) == 512)
            {
                fseek(file, -512, SEEK_CUR);
                while (!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) && fread(buffer, 1, 512, file) == 512)
                {
                    fwrite(buffer, 1, 512, image);
                    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
                    {
                        fseek(file, -512, SEEK_CUR);
                        //fseek(image, -512, SEEK_CUR);
                    }
                }
            }
            fclose(image);
            file_num++;
        }
    }
    free(buffer);
    fclose(file);
    return 0;
}
