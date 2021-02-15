#include "helpers.h"
#include <math.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            // averages the red, green, and blue values for each pixel
            int average = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);
            // the value of 'average' is set to the value of the red, green, and blue values for each pixel
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }

    }
}

int cap(int value)
{
    return value > 255 ? 255 : value;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            int sepiaRed = cap(round(0.393 * red + 0.769 * green + 0.189 * blue));
            int sepiaGreen = cap(round(0.349 * red + 0.686 * green + 0.168 * blue));
            int sepiaBlue = cap(round(0.272 * red + 0.534 * green + 0.131 * blue));

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

void swap(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    // swaps the values of 2 pixels
    RGBTRIPLE temp = *pixel1;
    *pixel1 = *pixel2;
    *pixel2 = temp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int start = 0;
    int end = width - 1;

    // loops through each row and swaps the values from the beginning of the array and the end
    for (int i = 0; i < height; i++)
    {
        while (start < end)
        {
            swap(&image[i][start], &image[i][end]);

            start++;
            end--;
        }

        start = 0;
        end = width - 1;
    }
}

bool is_valid_pixel(int i, int j, int height, int width)
{
    // checks if the values are in the correct boundaries
    return i >= 0 && i < height && j >= 0 && j < width;
}

RGBTRIPLE get_blurred_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int redValue, blueValue, greenValue;
    redValue = blueValue = greenValue = 0;
    int numOfValidPixels = 0;

    // will look at the current pixel, pixel behind, above, under, infront, etc.
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            int new_i = i + di;
            int new_j = j + dj;
            if (is_valid_pixel(new_i, new_j, height, width))
            {
                numOfValidPixels++;
                redValue += image[new_i][new_j].rgbtRed;
                blueValue += image[new_i][new_j].rgbtBlue;
                greenValue += image[new_i][new_j].rgbtGreen;
            }
        }
    }
    RGBTRIPLE blurred_pixel;
    // sets the red, green, blue values to the average of the other pixels.
    blurred_pixel.rgbtRed = round((float) redValue / numOfValidPixels);
    blurred_pixel.rgbtBlue = round((float) blueValue / numOfValidPixels);
    blurred_pixel.rgbtGreen = round((float) greenValue / numOfValidPixels);
    return blurred_pixel;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];

    // each pixel will be run through the 'get_blurred_pixel' function
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = get_blurred_pixel(i, j, height, width, image);
        }
    }

    // each pixel's value will be changed to a new value
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
    return;
}
