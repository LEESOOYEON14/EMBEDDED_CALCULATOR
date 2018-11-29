#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//#include "bitmap.h"
#include "../header/bitmap.h"


void read_pixels(Bitmap *bitmap, char *filename) {
    
    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;
    int padding = get_padding(width);
    unsigned int offset = bitmap->file_header->bfOffBits;

    FILE *fp = fopen(filename, "rb");
    
    // Move the file pointer to the start of the pixel array
    fseek(fp, offset, SEEK_SET);

    // Allocate memory for the pixel array (excluding padding bytes)
    byte *pixel_array = malloc(width * height * 3);

    for (int row = 0; row < height; row++) {

        fread(&pixel_array[row*(width*3)], sizeof(byte)*3, width, fp);

        byte padding_byte;
        for (int p = 0; p < padding; p++) {
            fread(&padding_byte, sizeof(byte), 1, fp);
        }
    }

    fclose(fp);
    bitmap->pixel_array = pixel_array;
}

void free_bitmap(Bitmap *bitmap) {
    free(bitmap->file_header);
    free(bitmap->info_header);
    free(bitmap->pixel_array);
    free(bitmap);
}

int get_padding(int width) {
    int padding = 0; //set padding to 0 by default

    // If row size is not a multiple of 4
    if ((width*3) % 4 != 0) {
        padding = 4 - ((width*3) % 4);
    }

    return padding;
}

Pixel *get_pixel(Bitmap *bitmap, int row, int col) {
    Pixel *pixel = NULL;
    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;

    if (col >= width) {
        col = width - (col % width);
    } else if (col < 0) {
        col = -col;
    }

    if (row >= height) {
        row = height - (row % height);
    } else if (row < 0) {
        row = -row;
    }

    pixel = (Pixel*) &(bitmap->pixel_array[row*(width*3) + (col*3)]);

    return pixel;
}
