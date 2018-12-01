#include <stdlib.h>
#include "../header/bitmap.h"
#include "../header/blur.h"

void horizontal_blur(Bitmap *bitmap, int radius) {
    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;

    byte *blurred_array = malloc(width * height * 3);

    for (int row = 0; row < height; row++) {
        int sum_b = 0;
        int sum_g = 0;
        int sum_r = 0;
        int count = 0;

        for (int i = -radius; i <= radius; i++) {
            Pixel *pixel = get_pixel(bitmap, row, i);
            sum_b += pixel->b;
            sum_g += pixel->g;
            sum_r += pixel->r;
            count++;
        }

        byte avg_b = (byte) (sum_b / count);
        byte avg_g = (byte) (sum_g / count);
        byte avg_r = (byte) (sum_r / count);

        set_pixel(blurred_array, width, row, 0, avg_b, avg_g, avg_r);

        for (int col = 1; col < width; col++) {
            Pixel *pixel = get_pixel(bitmap, row, col-radius-1);
            sum_b -= pixel->b;
            sum_g -= pixel->g;
            sum_r -= pixel->r;

            pixel = get_pixel(bitmap, row, col+radius);
            sum_b += pixel->b;
            sum_g += pixel->g;
            sum_r += pixel->r;

            avg_b = (byte) (sum_b / count);
            avg_g = (byte) (sum_g / count);
            avg_r = (byte) (sum_r / count);

            set_pixel(blurred_array, width, row, col, avg_b, avg_g, avg_r);
        }
    }

    free(bitmap->pixel_array);

    bitmap->pixel_array = blurred_array;
}

void vertical_blur(Bitmap *bitmap, int radius) {
    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;

    byte *blurred_array = malloc(width * height * 3);

    for (int col = 0; col < width; col++) {
        int sum_b = 0;
        int sum_g = 0;
        int sum_r = 0;
        int count = 0;

        for (int i = -radius; i <= radius; i++) {
            Pixel *pixel = get_pixel(bitmap, i, col);
            sum_b += pixel->b;
            sum_g += pixel->g;
            sum_r += pixel->r;
            count++;
        }

        byte avg_b = (byte) (sum_b / count);
        byte avg_g = (byte) (sum_g / count);
        byte avg_r = (byte) (sum_r / count);

        set_pixel(blurred_array, width, 0, col, avg_b, avg_g, avg_r);

        for (int row = 1; row < height; row++) {
            Pixel *pixel = get_pixel(bitmap, row-radius-1, col);
            sum_b -= pixel->b;
            sum_g -= pixel->g;
            sum_r -= pixel->r;

            pixel = get_pixel(bitmap, row+radius, col);
            sum_b += pixel->b;
            sum_g += pixel->g;
            sum_r += pixel->r;

            avg_b = (byte) (sum_b / count);
            avg_g = (byte) (sum_g / count);
            avg_r = (byte) (sum_r / count);

            set_pixel(blurred_array, width, row, col, avg_b, avg_g, avg_r);
        }
    }

    free(bitmap->pixel_array);

    bitmap->pixel_array = blurred_array;
}


void set_pixel(byte *pixel_array, int width, int row, int col, byte b, byte g, byte r) {
    pixel_array[row*(width*3) + (col*3+B)] = b;
    pixel_array[row*(width*3) + (col*3+G)] = g;
    pixel_array[row*(width*3) + (col*3+R)] = r;
}
