#include "helpers.h"
#include <math.h>


int limit(int color)
{
    if (color >= 255)
    {
        return 255;
    }
    else
    {
        return color;
    }
}


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int rgbtGray;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rgbtGray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = rgbtGray;
            image[i][j].rgbtGreen = rgbtGray;
            image[i][j].rgbtRed = rgbtGray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE cur = image[i][j];

            int sepiaRed = round(.393 * cur.rgbtRed + .769 * cur.rgbtGreen + .189 * cur.rgbtBlue);
            int sepiaGreen = round(.349 * cur.rgbtRed + .686 * cur.rgbtGreen + .168 * cur.rgbtBlue);
            int sepiaBlue = round(.272 * cur.rgbtRed + .534 * cur.rgbtGreen + .131 * cur.rgbtBlue);

            image[i][j].rgbtRed = limit(sepiaRed);
            image[i][j].rgbtGreen = limit(sepiaGreen);
            image[i][j].rgbtBlue = limit(sepiaBlue);

        }

    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width -1 -j];
            image[i][width -1 -j] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int h_range[] = {i-1, i, i+1};
            int w_range[] = {j-1, j, j+1};

            double totalRed = 0;
            double totalGreen = 0;
            double totalBlue = 0;

            int count = 0;

            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    int h_cord = h_range[x];
                    int w_cord = w_range[y];

                    if (h_cord >= 0 && w_cord >= 0 && h_cord < height && w_cord < width)
                    {
                        totalRed += image[h_cord][w_cord].rgbtRed;
                        totalGreen += image[h_cord][w_cord].rgbtGreen;
                        totalBlue += image[h_cord][w_cord].rgbtBlue;

                        count++;

                    }
                }
            }

            temp[i][j].rgbtRed = round(totalRed / count);
            temp[i][j].rgbtGreen = round(totalGreen / count);
            temp[i][j].rgbtBlue = round(totalBlue / count);


        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
        
    }

    return;
}


