#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //loop through every column
    int i;
    int j = 0;
    for (i = 0; i <= width; i++)
    {
        
        RGBTRIPLE pixel = image[j][i];
        
        image[j][i].rgbtRed = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);
        image[j][i].rgbtGreen = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);
        image[j][i].rgbtBlue = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);
        
        if (i == width)
        {
            i = 0;
            j++;
            if (j == height)
            {
                return;
            }
        }
    }
    return;
}
