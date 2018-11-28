#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "bitmap.h"


void write_bitmap(Bitmap *bitmap, char *fileout)
{
    FILE *fp = fopen(fileout, "wb");

    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;
    int padding = get_padding(width);

    
    fwrite(bitmap->file_header, sizeof(BITMAPFILEHEADER), 1, fp);
    fwrite(bitmap->info_header, sizeof(BITMAPINFOHEADER), 1, fp);

    
    byte *pixel_array = bitmap->pixel_array;

    for (int row = 0; row < height; row++) 
    {
        fwrite(&pixel_array[row*(width*3)], sizeof(byte)*3, width, fp);
        for (int p = 0; p < padding; p++) 
        {
            byte null = 0;
            fwrite(&null, sizeof(byte), 1, fp);
        }
    }

    fclose(fp);
}
