#include <stdlib.h>
#include "../header/bitmap.h"
#include "../header/crop.h"



void crop_filter(Bitmap *bitmap, int top, int bottom, int left, int right) 
{
    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;
    int new_width = width - left - right;
    int new_height = height - top - bottom;
    int new_padding = get_padding(new_width);

    byte *cropped_array = malloc(new_width * new_height * 3);


    int r = 0;

    for (int row = bottom; row < height-top; row++)
    {
        int c = 0;
        for (int col = left; col < (width-right); col++)
        {
            Pixel *pixel = get_pixel(bitmap, row, col);
            cropped_array[r*(new_width*3) + (c+B)] = pixel->b;
            cropped_array[r*(new_width*3) + (c+G)] = pixel->g;
            cropped_array[r*(new_width*3) + (c+R)] = pixel->r;
            c+=3;
        }
        r++;
    }

    bitmap->info_header->width = new_width;
    bitmap->info_header->height = new_height;
    bitmap->info_header->biSize = (new_width*3 + new_padding) * new_height;
    bitmap->file_header->bmp_size = (bitmap->info_header->biSize) + BMPHEADER_SIZE;

    free(bitmap->pixel_array);
    bitmap->pixel_array = cropped_array;
}
