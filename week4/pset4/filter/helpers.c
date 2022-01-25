#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through image matrix
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            // Take average and set all 3 color values to that average
            int rgbAverage = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;

            image[i][j].rgbtRed = rgbAverage;
            image[i][j].rgbtGreen = rgbAverage;
            image[i][j].rgbtBlue = rgbAverage;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through image matrix
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            // when even width
            if(width % 2 == 0)
            {
                if(j * 2 < width)
                {
                    RGBTRIPLE tmp = image[i][j];
                    image[i][j] = image[i][width - (j + 1)];
                    image[i][width - (j + 1)] = tmp;
                }
            }

            // when odd width
            else
            {
                if(j * 2 < width - 1)
                {
                    int reflection_p = (width - 1) / 2;
                    RGBTRIPLE tmp = image[i][reflection_p - j];
                    image[i][reflection_p - j] = image[i][reflection_p + j];
                    image[i][reflection_p + j] = tmp;
                }
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Allocate memory for blurred image
    RGBTRIPLE(*image_b)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image_b == NULL)
    {
        fprintf(stderr, "Not enough memory to store image.\n");
        return;
    }

    // Iterate through every pixel in image matrix
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            // Setting up parameters for 3x3 grid

            // For x-axis
            int start_x = i - 1;
            if(start_x < 0)
            {
                start_x = 0;
            }

            // For x-axis
            int end_x = i + 2;
            if(end_x > height)
            {
                end_x = height;
            }

            // For y-axis
            int start_y = j - 1;
            if(start_y < 0)
            {
                start_y = 0;
            }

            // For y-axis
            int end_y = j + 2;
            if(end_y > width)
            {
                end_y = width;
            }

            // Initialize each RGB value sum
            int sum_rgbRed = 0;
            int sum_rgbGreen = 0;
            int sum_rgbBlue = 0;
            int grid_total = 0;

            // Go through 3x3 grid and collect sums
            for(int o = start_x; o < end_x; o++)
            {
                for(int u = start_y; u < end_y; u++)
                {
                    sum_rgbRed += image[o][u].rgbtRed;
                    sum_rgbGreen += image[o][u].rgbtGreen;
                    sum_rgbBlue += image[o][u].rgbtBlue;
                    grid_total++;
                }
            }

            // Average each sum and set it as new color value for image[i][j]
            if(grid_total > 0)
            {

            int averageRed = (sum_rgbRed / grid_total);
            int averageGreen = (sum_rgbGreen / grid_total);
            int averageBlue = (sum_rgbBlue / grid_total);
            image_b[i][j].rgbtRed = averageRed;
            image_b[i][j].rgbtGreen = averageGreen;
            image_b[i][j].rgbtBlue = averageBlue;

            }
        }
    }
    for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                image[i][j] = image_b[i][j];
            }
        }
    free(image_b);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
