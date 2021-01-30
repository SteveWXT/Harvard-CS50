#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BTYE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    FILE *raw = fopen(argv[1], "r");

    if (raw == NULL)
    {
        fprintf(stderr, "Cannot open file!\n");
        return 2;
    }

    BTYE *block = malloc(512 * sizeof(BTYE));
    char *filename = malloc(8 * sizeof(char));
    int count = 0;
    FILE *image = NULL;

    //read data as blocks until reaching the end of the file
    while (fread(block, sizeof(BTYE), 512, raw) == 512)
    {
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            if (image != NULL)
            {
                fclose(image);
            }

            sprintf(filename, "%03i.jpg", count);
            image = fopen(filename, "w");

            if (image == NULL)
            {
                fprintf(stderr, "Cannot write image%03i into the file!\n", count);
                free(block);
                free(filename);
                return 3;
            }

            fwrite(block, sizeof(BTYE), 512, image);
            count++;

        }
        else
        {
            if (image != NULL)
            {
                fwrite(block, sizeof(BTYE), 512, image);
            }
        }
    }


    if (raw != NULL)
    {
        fclose(raw);
    }

    if (image != NULL)
    {
        fclose(image);
    }

    free(block);
    free(filename);

    return 0;

}