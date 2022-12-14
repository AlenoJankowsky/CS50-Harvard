#include "helpers.h"
#include <cs50.h>
#include <math.h>
#include <stdio.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int grayscaleHeight = 0; grayscaleHeight < height; grayscaleHeight++) {
        for (int grayscaleWidth = 0; grayscaleWidth < width; grayscaleWidth++) {
            int averageColorValue = round((image[grayscaleHeight][grayscaleWidth].rgbtBlue + image[grayscaleHeight][grayscaleWidth].rgbtGreen + image[grayscaleHeight][grayscaleWidth].rgbtRed) / 3.0);
            image[grayscaleHeight][grayscaleWidth].rgbtBlue = averageColorValue;
            image[grayscaleHeight][grayscaleWidth].rgbtGreen = averageColorValue;
            image[grayscaleHeight][grayscaleWidth].rgbtRed = averageColorValue;
        }
    }

    return;
}

void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    for (int sepiaHeight = 0; sepiaHeight < height; sepiaHeight++) {
        for (int sepiaWidth = 0; sepiaWidth < width; sepiaWidth++) {
            float originalBlue = image[sepiaHeight][sepiaWidth].rgbtBlue;
            float originalGreen = image[sepiaHeight][sepiaWidth].rgbtGreen;
            float originalRed = image[sepiaHeight][sepiaWidth].rgbtRed;

            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);

            bool blueHasOverflow = sepiaBlue > 255;
            bool greenHasOverflow = sepiaGreen > 255;
            bool redHasOverflow = sepiaRed > 255;

            if (blueHasOverflow) {
                sepiaBlue = 255;
            }

            if (greenHasOverflow) {
                sepiaGreen = 255;
            }

            if (redHasOverflow) {
                sepiaRed = 255;
            }

            image[sepiaHeight][sepiaWidth].rgbtBlue = sepiaBlue;
            image[sepiaHeight][sepiaWidth].rgbtGreen = sepiaGreen;
            image[sepiaHeight][sepiaWidth].rgbtRed = sepiaRed;
        }
    }

    return;
}

void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int reflectedHeight = 0; reflectedHeight < height; reflectedHeight++) {
        for (int reflectedWidth = 0; reflectedWidth < width; reflectedWidth++) {
            image[reflectedHeight][reflectedWidth] = image[reflectedHeight][width * 2 - reflectedWidth];
        }
    }

    return;
}

void blur(int height, int width, RGBTRIPLE image[height][width]) {
    int averageBlue;
    int averageGreen;
    int averageRed;

    for (int blurHeight = 0; blurHeight < height; blurHeight++) {
        for (int blurWidth = 0; blurWidth < width; blurWidth++) {
            int validCounter = 0;
            int currentBlurBlueValue;
            int currentBlurGreenValue;
            int currentBlurRedValue;
            int sumOfBlue = 0;
            int sumOfGreen = 0;
            int sumOfRed = 0;
            
            for (int heightIterator = -1; heightIterator <= 1; heightIterator++) {
                for (int widthIterator = -1; widthIterator <= 1; widthIterator++) {
                    bool pixelIsValid = (blurHeight + heightIterator) >= 0 && (blurHeight + heightIterator) < height && (blurWidth + widthIterator) >= 0 && (blurWidth + widthIterator) < width;

                    if (!pixelIsValid) {
                        continue;
                    }

                    currentBlurBlueValue = image[blurHeight + heightIterator][blurWidth + widthIterator].rgbtBlue;
                    currentBlurGreenValue = image[blurHeight + heightIterator][blurWidth + widthIterator].rgbtGreen;
                    currentBlurRedValue = image[blurHeight + heightIterator][blurWidth + widthIterator].rgbtRed;

                    if (pixelIsValid) {
                        sumOfBlue = sumOfBlue + currentBlurBlueValue;
                        sumOfGreen = sumOfGreen + currentBlurGreenValue;
                        sumOfRed = sumOfRed + currentBlurRedValue;
                        validCounter++;
                    }                    
                }   
            }

            averageBlue = round(sumOfBlue / validCounter);
            averageGreen = round(sumOfGreen / validCounter);
            averageRed = round(sumOfRed / validCounter);

            image[blurHeight][blurWidth].rgbtBlue = averageBlue;
            image[blurHeight][blurWidth].rgbtGreen = averageGreen;
            image[blurHeight][blurWidth].rgbtRed = averageRed;
        } 
    }

    return;
}

