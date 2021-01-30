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


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int h_range[] = {i-1, i, i+1};
            int w_range[] = {j-1, j, j+1};

            double totalRedX = 0;
            double totalGreenX = 0;
            double totalBlueX = 0;
            double totalRedY = 0;
            double totalGreenY = 0;
            double totalBlueY = 0;


            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    int h_cord = h_range[x];
                    int w_cord = w_range[y];


                    if (h_cord >= 0 && w_cord >= 0 && h_cord < height && w_cord < width)
                    {
                        if (h_cord == i-1 && w_cord == j-1)
                        {
                            totalRedX += image[h_cord][w_cord].rgbtRed * (-1);
                            totalGreenX += image[h_cord][w_cord].rgbtGreen * (-1);
                            totalBlueX += image[h_cord][w_cord].rgbtBlue * (-1);

                            totalRedY += image[h_cord][w_cord].rgbtRed * (-1);
                            totalGreenY += image[h_cord][w_cord].rgbtGreen * (-1);
                            totalBlueY += image[h_cord][w_cord].rgbtBlue * (-1);

                        }
                        else if (h_cord == i && w_cord == j-1)
                        {
                            totalRedX += image[h_cord][w_cord].rgbtRed * (-2);
                            totalGreenX += image[h_cord][w_cord].rgbtGreen * (-2);
                            totalBlueX += image[h_cord][w_cord].rgbtBlue * (-2);
                        }
                        else if (h_cord == i+1 && w_cord == j-1)
                        {
                            totalRedX += image[h_cord][w_cord].rgbtRed * (-1);
                            totalGreenX += image[h_cord][w_cord].rgbtGreen * (-1);
                            totalBlueX += image[h_cord][w_cord].rgbtBlue * (-1);

                            totalRedY += image[h_cord][w_cord].rgbtRed;
                            totalGreenY += image[h_cord][w_cord].rgbtGreen;
                            totalBlueY += image[h_cord][w_cord].rgbtBlue;
                        }
                        else if (h_cord == i-1 && w_cord == j)
                        {

                            totalRedY += image[h_cord][w_cord].rgbtRed * (-2);
                            totalGreenY += image[h_cord][w_cord].rgbtGreen * (-2);
                            totalBlueY += image[h_cord][w_cord].rgbtBlue * (-2);
                        }
                        else if (h_cord == i+1 && w_cord == j)
                        {

                            totalRedY += image[h_cord][w_cord].rgbtRed * 2;
                            totalGreenY += image[h_cord][w_cord].rgbtGreen * 2;
                            totalBlueY += image[h_cord][w_cord].rgbtBlue * 2;
                        }
                        else if (h_cord == i-1 && w_cord == j+1)
                        {

                            totalRedX += image[h_cord][w_cord].rgbtRed;
                            totalGreenX += image[h_cord][w_cord].rgbtGreen;
                            totalBlueX += image[h_cord][w_cord].rgbtBlue;

                            totalRedY += image[h_cord][w_cord].rgbtRed * (-1);
                            totalGreenY += image[h_cord][w_cord].rgbtGreen * (-1);
                            totalBlueY += image[h_cord][w_cord].rgbtBlue * (-1);

                        }
                        else if (h_cord == i && w_cord == j+1)
                        {

                            totalRedX += image[h_cord][w_cord].rgbtRed * 2;
                            totalGreenX += image[h_cord][w_cord].rgbtGreen * 2;
                            totalBlueX += image[h_cord][w_cord].rgbtBlue * 2;
                        }
                        else if (h_cord == i+1 && w_cord == j+1)
                        {

                            totalRedX += image[h_cord][w_cord].rgbtRed;
                            totalGreenX += image[h_cord][w_cord].rgbtGreen;
                            totalBlueX += image[h_cord][w_cord].rgbtBlue;

                            totalRedY += image[h_cord][w_cord].rgbtRed;
                            totalGreenY += image[h_cord][w_cord].rgbtGreen;
                            totalBlueY += image[h_cord][w_cord].rgbtBlue;
                        }

                    }
                }
            }

            temp[i][j].rgbtRed = limit(round(sqrt(pow(totalRedX,2) + pow(totalRedY,2))));
            temp[i][j].rgbtGreen = limit(round(sqrt(pow(totalGreenX,2) + pow(totalGreenY,2))));
            temp[i][j].rgbtBlue = limit(round(sqrt(pow(totalBlueX,2) + pow(totalBlueY,2))));

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
