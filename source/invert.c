#include "../header/bitmap.h"
#include "../header/invert.h"

void invert_filter(Bitmap *bitmap) {
    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Pixel *pixel = get_pixel(bitmap, row, col);

            pixel->b = ~(pixel->b);
            pixel->g = ~(pixel->g);
            pixel->r = ~(pixel->r);
        }
    }
}
