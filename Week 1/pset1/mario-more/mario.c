#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get height and make sure it's between 1 and 8
    int height = 0;
    while (height < 1 || height > 8)
    {
        height = get_int("Height: ");
    }

    // Print out the pyramid
    for (int i = 0; i < height; i++)
    {
        // Spaces for the first side of the hashes
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }

        // Add the hashes based on the layer you're on
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        // Spacing
        printf("  ");

        //
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}