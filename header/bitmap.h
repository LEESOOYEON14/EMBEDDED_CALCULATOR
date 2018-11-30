#ifndef BITMAP_H
#define BITMAP_H

#define BMPHEADER_SIZE 54
#define BYTES_IN_PIXEL 3

#define B 0
#define G 1
#define R 2

// Tell the compiler not to add alignment/padding bytes to the structs in memory
// Necessary to make the struct equivalent to the BMP header structure

typedef unsigned char byte;

#pragma pack(push, 1)

typedef struct {
    // 14 bytes
    unsigned char header1;                  // B
    unsigned char header2;                  // M
    unsigned int bmp_size;                  // size of BMP file in bytes
    unsigned short bfReserved1;               // 2 bytes reserved value (unused)
    unsigned short bfReserved2;
    unsigned int bfOffBits;        // starting address of pixel array
} BITMAPFILEHEADER;

typedef struct {
    // 40 bytes
    // Based on the Windows BITMAPINFOHEADER standard
    unsigned int biSize;           // size of BITMAPINFOHEADER
    int width;                              // bitmap width in pixels (signed)
    int height;                             // bitmap height in pixels (signed)
    unsigned short biPlanes;            // must be 1
    unsigned short biBitCount;          // typically 1,4,8,16,24,32
    unsigned int biCompression;
    unsigned int biSizeImage;                // size of raw bitmap data
    unsigned int biXPelsPerMeter;                     // horizontal resolution
    unsigned int biYPelsPerMeter;                     // vertical resolution
    unsigned int biClrUsed;             // number of colors in palette
    unsigned int biClrImportant;          // default 0
} BITMAPINFOHEADER;

#pragma pack(pop)

typedef struct  
{
    BITMAPFILEHEADER *file_header;
    BITMAPINFOHEADER *info_header;
    byte *pixel_array;
}Bitmap ;

typedef struct 
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
}Pixel ;

int get_padding(int width);

Bitmap *new_bitmap(char *filename);

void read_pixels(Bitmap *bitmap, char *filename);
void free_bitmap(Bitmap *bitmap);
void write_bitmap(Bitmap *bitmap, char *fileout);

Pixel *get_pixel(Bitmap *bitmap, int row, int col);

#endif
