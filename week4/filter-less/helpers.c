#include "helpers.h"
#include "math.h"

// Convert image to grayscale
// make sure the red, green, and blue values are all the same value, you can take the **average** of
// the red, green, and blue values to determine what shade of grey to make the new pixel passar por
// todo array com um loop, pegando a média de todo o vermelho, todo o verde e todo azul de toda
// imagem; depois disso, atualizar a imagem com os novos valores
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float averageColor =
                (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            // atualiza valores
            averageColor = round(averageColor); // pra que teste de imagem de 1 pixel funcione
            image[i][j].rgbtRed = averageColor;
            image[i][j].rgbtGreen = averageColor;
            image[i][j].rgbtBlue = averageColor;
        }
    }
    return;
}

// Convert image to sepia
// For each pixel, the sepia color values should be calculated based on the original color values
// per the below.

// sepiaRed = .393 * originalRed + .76.09 * originalGreen + .189 * originalBlue
// sepiaGreen = .349 * originalRed + .6.086.0 * originalGreen + .16.08 * originalBlue
// sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

// Of course, the result of each of these formulas may not be an integer, but each value could be
// rounded to the nearest integer. It’s also possible that the result of the formula is a number
// greater than 255, the maximum value for an 8-bit color value. In that case, the red, green, and
// blue values should be capped at 255.

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float maxSepia = 255.0;
            float sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                   .189 * image[i][j].rgbtBlue);
            float sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                     .168 * image[i][j].rgbtBlue);
            float sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                    .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtRed = fminf(sepiaRed, maxSepia);
            image[i][j].rgbtGreen = fminf(sepiaGreen, maxSepia);
            image[i][j].rgbtBlue = fminf(sepiaBlue, maxSepia);
        }
    }
    return;
}

// Reflect image horizontally
// Any pixels on the left side of the image should end up on the right, and vice versa

// Implement reflect
// Using what you know about the algorithm for image reflection, you know that in the reflect
// function, you’ll need to swap the values of pixels on opposite sides of a row. Write some
// pseudocode to help you get started:

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2;
             j++) // n precisa loop toda fila horizontal, só em metade da imagem
        {
            // Swap pixels
            RGBTRIPLE tempImg = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tempImg;
        }
    }
}
//   You store the value of image[i][j] in tempImg. This is important because you’re about to
//   overwrite image[i][j]. You assign the value of image[i][width - j - 1] to image[i][j]. This
//   effectively swaps the two pixels. Finally, you assign the value of tempImg to image[i][width -
//   j - 1]. This completes the swap by putting the original value of image[i][j] into
//   image[i][width - j - 1].

// Recall from lecture how we implemented swapping two values with a temporary variable.
// And now’s a good time to think about your nested for loops. The outer for loop iterates over
// every row, while the inner for loop iterates over every pixel in that row. To successfully
// reflect a row, though, need you iterate over every pixel in it?

// Blur image
// new value of each pixel would be the average of the values of all of the pixels that are within 1
// row and column of the original pixel (forming a 3x3 box) taking each pixel and, for each color
// value, giving it a new value by averaging the color values of neighboring pixels.

// When implementing the blur algorithm, you might find that blurring one pixel ends up affecting
// the blur of another pixel. Therefore, it might be best to create a copy of image by declaring a
// new, two-dimensional array with code like RGBTRIPLE copy[height][width]; Then copy image into
// copy, pixel by pixel, with nested for loops, like so:
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width]; // line,column
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // corner 0,0
            if (i == 0 && j == 0)
            {
                copy[i][j].rgbtBlue =
                    round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                           image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) /
                          4.0);
                copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed +
                                            image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) /
                                           4.0);
                copy[i][j].rgbtGreen =
                    round((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                           image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) /
                          4.0);
            }
            // corner height,0
            else if (i == (height - 1) && j == 0)
            {
                copy[i][j].rgbtBlue =
                    round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue +
                           image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) /
                          4.0);
                copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed +
                                            image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed) /
                                           4.0);
                copy[i][j].rgbtGreen =
                    round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen +
                           image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) /
                          4.0);
            }
            // corner 0,width
            else if (i == 0 && j == (width - 1))
            {
                copy[i][j].rgbtBlue =
                    round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                           image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) /
                          4.0);
                copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                                            image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) /
                                           4.0);
                copy[i][j].rgbtGreen =
                    round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                           image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) /
                          4.0);
            }
            // corner height,width
            else if (i == (height - 1) && j == (width - 1))
            {
                copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                             image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue) /
                                            4.0);
                copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                            image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed) /
                                           4.0);
                copy[i][j].rgbtGreen =
                    round((image[i][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                           image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen) /
                          4.0);
            }
            // top line (i=0)
            else if (i == 0 && j != 0 && j < (width - 1))
            {
                copy[i][j].rgbtBlue =
                    round((image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                           image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                           image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) /
                          6.0);
                copy[i][j].rgbtRed = round((image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                            image[i][j].rgbtRed + image[i + 1][j].rgbtRed +
                                            image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) /
                                           6.0);
                copy[i][j].rgbtGreen =
                    round((image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                           image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                           image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) /
                          6.0);
            }
            // bottom line (i=height-1)
            else if (i == (height - 1) && j != 0 && j < (width - 1))
            {
                copy[i][j].rgbtBlue =
                    round((image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                           image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue +
                           image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) /
                          6.0);
                copy[i][j].rgbtRed = round((image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                            image[i][j].rgbtRed + image[i - 1][j].rgbtRed +
                                            image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed) /
                                           6.0);
                copy[i][j].rgbtGreen =
                    round((image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                           image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen +
                           image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen) /
                          6.0);
            }

            // left column (j=0)
            else if (i != 0 && i < (height - 1) && j == 0)
            {
                copy[i][j].rgbtBlue =
                    round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                           image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                           image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) /
                          6.0);
                copy[i][j].rgbtRed = round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                            image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                            image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) /
                                           6.0);
                copy[i][j].rgbtGreen =
                    round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                           image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                           image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) /
                          6.0);
            }

            // right column (j=width-1)
            else if (i != 0 && i < (height - 1) && j == (width - 1))
            {
                copy[i][j].rgbtBlue =
                    round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                           image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue +
                           image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) /
                          6.0);
                copy[i][j].rgbtRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                            image[i][j - 1].rgbtRed + image[i][j].rgbtRed +
                                            image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) /
                                           6.0);
                copy[i][j].rgbtGreen =
                    round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                           image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen +
                           image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) /
                          6.0);
            }
            else
            {
                copy[i][j] = image[i][j];

                float middleBlue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                          image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                                          image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                          image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                          image[i + 1][j + 1].rgbtBlue) /
                                         9.0);
                float middleRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                         image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed +
                                         image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                         image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                                         image[i + 1][j + 1].rgbtRed) /
                                        9.0);
                float middleGreen =
                    round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                           image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                           image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                           image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                           image[i + 1][j + 1].rgbtGreen) /
                          9.0);

                copy[i][j].rgbtBlue = middleBlue;
                copy[i][j].rgbtRed = middleRed;
                copy[i][j].rgbtGreen = middleGreen;
            }
            // }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}
