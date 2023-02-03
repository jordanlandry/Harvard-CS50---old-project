#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE_OF_BUFFER 512


// JPEG Header - 0xff, 0xd8, 0xff, 0xe_
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("No Input file.");
        return 1;
    }

    FILE *input = fopen(argv[1], "r"); // Data Card

    if (input == NULL)
    {
        printf("Could not open raw card.");
        return 1;
    }

    unsigned char buffer[SIZE_OF_BUFFER];
    int filecount = 0;
    FILE *picture = NULL;
    bool jpg_found = false;

    // If buffer reads not 512 bytes, it's not a JPEG
    while (fread(buffer, SIZE_OF_BUFFER, 1, input) == 1)
    {
        // Common JPEG start pattern
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (jpg_found)
            {
                // We found the start of a new pic so close out current picture
                fclose(picture);
            }

            else
            {
                // jpg discovered and now we have the green light to write
                jpg_found = true;
            }

            char filename[8];
            sprintf(filename, "%03d.jpg", filecount);
            picture = fopen(filename, "a");
            filecount++;
        }

        if (jpg_found)
        {
            // write 512 bytes to file once we start finding jpgs
            fwrite(&buffer, SIZE_OF_BUFFER, 1, picture);
        }
    }

    fclose(input);
    fclose(picture);


    return 0;
}