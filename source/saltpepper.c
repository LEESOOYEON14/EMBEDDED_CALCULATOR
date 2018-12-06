
#include <stdlib.h>

#include "../header/bitmap.h"
#include "../header/saltpepper.h"

void set_pixel(byte *pixel_array, int width, int row, int col, byte b, byte g, byte r) {
    pixel_array[row*(width*3) + (col*3+B)] = b;
    pixel_array[row*(width*3) + (col*3+G)] = g;
    pixel_array[row*(width*3) + (col*3+R)] = r;
}


void saltpepper(Bitmap *bitmap, int radius)
{
  int width = bitmap->info_header->width;
  int height = bitmap->info_header->height;
  
  int noise_pixel = (int){(double)(width*height*3)*radius};
  
  byte *saltpepper_array = malloc(width * height * 3);

  for(int row = 0; row < height; row++)
  {
    for(int col = 1; col < width; col++ )
    {
      int r = rand() % width;
      int c = rand() % height;
      int pixel_b =0;
      int pixel_g =0;
      int pixel_r =0;

      int ch = rand() % 3;
      Pixel *pixel = get_pixel(bitmap,r,c);

      noise_pixel = (rand() % 2 ==1 ) ? 255: 0;

      pixel_b = pixel->b;
      pixel_g = pixel->g;
      pixel_r = pixel->r;
      
    
      set_pixel(saltpepper_array, width,row,col,noise_pixel, noise_pixel, noise_pixel);
     
      free(bitmap->pixel_array);
      bitmap->pixel_array = saltpepper_array;
    }
  }  
}
