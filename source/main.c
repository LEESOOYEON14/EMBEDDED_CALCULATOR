#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>

#include "../header/bitmap.h"
#include "../header/bitmap_write.h"
#include "../header/saltpepper.h"

int main(int argc, char *argv[])
{
  char *file_name = argv[1];
  char *file_out = argv[2]; 
  Bitmap *bitmap = new_bitmap(file_name);
  read_pixels(bitmap, file_name);
  saltpepper(bitmap,1);
  write_bitmap(bitmap, file_out);
  free_bitmap(bitmap);
  return 0;
}

