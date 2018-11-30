#ifndef BLUR_H
#define BLUR_H

void horizontal_blur(Bitmap *bitmap, int radius);
void vertical_blur(Bitmap *bitmap, int radius);

void set_pixel(byte *pixel_array, int width, int row, int col, byte b, byte g, byte r);


