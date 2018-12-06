#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "bitmap.h"
#include "bitmap_write.h"





int main(int argc, char*argv[])
{
  char *file_in = NULL;
  file_in = strdup(argv[1]);
  Bitmap *bitmap = new_bitmap(file_in);
  read_pixels(bitmap, file_in);
  printf("Image widh : %d\n, bitmap->info_header->width");
  return 0;
}

