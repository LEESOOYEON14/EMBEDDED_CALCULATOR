#include "../header/bitmap.h"

#include "threshold.h"



void threshold_filter(Bitmap *bitmap, float threshold) 
{

    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;

    for (int row = 0; row < height; row++) 
    {
        for (int col = 0; col < width; col++) 
        {
            Pixel *pixel = get_pixel(bitmap, row, col);
            float average = ((float)(pixel->b + pixel->g + pixel->r) / 3) / 255;
            if (average > threshold) 
            {
                pixel->b = 0xFF;
                pixel->g = 0xFF;
                pixel->r = 0xFF;
            } 
            else 
            {
                pixel->b = 0x00;
                pixel->g = 0x00;
                pixel->r = 0x00;
            }
        }
    }
}
