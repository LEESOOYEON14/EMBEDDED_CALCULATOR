#include "../header/bitmap.h"
#include "../header/monochrome.h"

void greyscale_filter(Bitmap *bitmap) {
    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Pixel *pixel = get_pixel(bitmap, row, col);

            float greyscale = LUMA_B * pixel->b + LUMA_G * pixel->g + LUMA_R * pixel->r;

            pixel->b = (unsigned char) greyscale;
            pixel->g = (unsigned char) greyscale;
            pixel->r = (unsigned char) greyscale;
        }
    }
}


void red_filter(Bitmap *bitmap) {
    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Pixel *pixel = get_pixel(bitmap, row, col);

            pixel->b = 0x00;
            pixel->g = 0x00;
        }
    }
}


void blue_filter(Bitmap *bitmap) {
    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Pixel *pixel = get_pixel(bitmap, row, col);

            pixel->g = 0x00;
            pixel->r = 0x00;
        }
    }
}


void green_filter(Bitmap *bitmap) {
    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Pixel *pixel = get_pixel(bitmap, row, col);

            pixel->b = 0x00;
            pixel->r = 0x00;
        }
    }
}
