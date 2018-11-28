#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../header/bitmap.h"
#include "bitmap_write.h"



void print_dimensions(Bitmap *bitmap)
{
    printf("Image width: %d\n", bitmap->info_header->width);
    printf("Image height: %d\n", bitmap->info_header->height);
}



int main(int argc, char*argv[])
{
  char *file_in = NULL;
  file_in = strdup(argv[1]);
  Bitmap *bitmap = new_bitmap(file_in);
  read_pixels(bitmap, file_in);
  print_dimensions(bitmap);
}

