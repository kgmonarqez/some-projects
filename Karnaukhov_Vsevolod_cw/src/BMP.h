#include <stdio.h>
#include <stdlib.h>

#pragma pack (push, 1)

typedef struct{
    unsigned char B;
    unsigned char G;
    unsigned char R;
}RGB;

typedef struct{
    unsigned short Signature;
    unsigned int FileSize;
    unsigned short Reserved1;
    unsigned short Reserved2;
    unsigned int FileOffsetToPixelArray;
}BITMAPFILEHEADER;

typedef struct{
    unsigned int Size;
    unsigned int Width;
    unsigned int Height;
    unsigned short Planes;
    unsigned short BitsPerPixelCount;
    unsigned int Compression;
    unsigned int ImageSize;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int ColorTableSize;
    unsigned int ColorTableImportant;
}BITMAPINFOHEADER;

typedef struct{
    BITMAPFILEHEADER BMFH;
    BITMAPINFOHEADER BMIH;
    RGB **data;
}BMP;

typedef struct{
    int x;
    int y;
}XoY;

void InitBMFH(BITMAPFILEHEADER *BMFH, size_t W, size_t H);
void InitBMIH(BITMAPINFOHEADER *BMIH, size_t W, size_t H);
void InitData(BMP *Image, size_t W, size_t H);
BMP InitBMP(size_t W, size_t H);
BMP OpenBMP(const char* path);
void SaveBMP(const char * path, BMP Image);

void painting(BMP *Image, RGB Color, size_t x, size_t y);
int RGBcmp(RGB color1, RGB color2);
char *check_coordinates(BMP Image, XoY p2, XoY p4);
BMP reflect(BMP Image, int axis, int dir, XoY p2, XoY p4, int security);
BMP area_cpy(BMP Image, XoY p2, XoY p4, XoY new_p2, int security);
BMP color_change(BMP Image, RGB old, RGB new);
int color_count(BMP Image, RGB color);