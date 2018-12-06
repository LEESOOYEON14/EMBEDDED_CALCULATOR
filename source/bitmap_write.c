#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../header/bitmap.h"
#include "../header/bitmap_write.h"

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

Bitmap *new_bitmap(char *filename) {
    Bitmap *bitmap = malloc(sizeof(Bitmap));
    BITMAPFILEHEADER *file_header;
    BITMAPINFOHEADER *info_header;
    byte *pixel_array = NULL;

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file %s: %d (%s)\n", filename, errno, strerror(errno));
        return NULL;
    } else {
        file_header = malloc(sizeof(BITMAPINFOHEADER));
        fread(file_header, sizeof(BITMAPFILEHEADER), 1, fp);

        if (file_header->header1 == 'B' && file_header->header2 == 'M') {
            info_header = malloc(sizeof(BITMAPINFOHEADER));
            fread(info_header, sizeof(BITMAPINFOHEADER), 1, fp);
        } else {
            printf("%s is not a valid bmp file.\n", filename);
            return NULL;
        }

        fclose(fp);
    }

    bitmap->file_header = file_header;
    bitmap->info_header = info_header;
    bitmap->pixel_array = pixel_array;

    return bitmap;
}
