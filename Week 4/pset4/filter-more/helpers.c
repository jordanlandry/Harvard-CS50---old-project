#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average the colours
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Set each  pixel to the average color
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];

            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Temp variable
    RGBTRIPLE temp[height][width];

    // Go through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Init the temp variable
            temp[i][j] = image[i][j];

            // Average colors for each spot
            float redSum = 0;
            float greenSum = 0;
            float blueSum = 0;
            int avgCount = 0;

            // Run through a 3x3 grid
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + k < 0 || i + k > height - 1)
                    {
                        continue;
                    }

                    if (j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }

                    // Add together each color in the pixel
                    redSum += image[i + k][j + l].rgbtRed;
                    greenSum += image[i + k][j + l].rgbtGreen;
                    blueSum += image[i + k][j + l].rgbtBlue;
                    avgCount++;

                }
            }

            // Calc average
            temp[i][j].rgbtRed = round(redSum / avgCount);
            temp[i][j].rgbtGreen = round(greenSum / avgCount);
            temp[i][j].rgbtBlue = round(blueSum / avgCount);
        }
    }


    // Update image with temp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int gxBlue = 0;
            int gyBlue = 0;
            int gxGreen = 0;
            int gyGreen = 0;
            int gxRed = 0;
            int gyRed = 0;

            for (int r = - 1; r < 2; r++)
            {
                for (int c = - 1; c < 2; c++)
                {
                    // If the current point is greater than the edge
                    if (i + r < 0 || i + r > height - 1)
                    {
                        continue;
                    }

                    // If the current point is greater than the edge
                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }

                    // Sobol is gX ^ 2 + gY ^ 2
                    // However we need to get the indiviual values of gY and gX
                    // for each RBG value
                    gxBlue += image[i + r][j + c].rgbtBlue * gx[r + 1][c + 1];
                    gyBlue += image[i + r][j + c].rgbtBlue * gy[r + 1][c + 1];

                    gxGreen += image[i + r][j + c].rgbtGreen * gx[r + 1][c + 1];
                    gyGreen += image[i + r][j + c].rgbtGreen * gy[r + 1][c + 1];

                    gxRed += image[i + r][j + c].rgbtRed * gx[r + 1][c + 1];
                    gyRed += image[i + r][j + c].rgbtRed * gy[r + 1][c + 1];
                }
            }

            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtBlue = blue;

            if (red > 255)
            {
                temp[i][j].rgbtRed = 255;
            }

            if (green > 255)
            {
                temp[i][j].rgbtGreen = 255;
            }

            if (blue > 255)
            {
                temp[i][j].rgbtBlue = 255;
            }

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
}
