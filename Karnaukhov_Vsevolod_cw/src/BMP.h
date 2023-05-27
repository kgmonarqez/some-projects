#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <math.h>

#define X 0
#define Y 1
#define DOWN 00
#define UP 01
#define LEFT 10
#define RIGHT 11
#define PI 3.14159265

#pragma pack(push, 1)
typedef struct{
    unsigned short Signature;
    unsigned int FileSize;
    unsigned short Reserved1;
    unsigned short Reserved2;
    unsigned int FileOffsetToPixelArray;
}BITMAPFILEHEADER;
#pragma pack(pop)

typedef struct{
    unsigned char B;
    unsigned char G;
    unsigned char R;
}RGB;

typedef struct{
    unsigned int Size;
    unsigned int Width;
    int Height;
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

BMP InitBMP(int W, int H);
RGB **InitData(int W, int H);

BMP OpenBMP(const char* path);
void SaveBMP(const char * path, BMP Image);

void data_free(BMP *Image);

void painting(BMP *Image, RGB Color, int x, int y);
void Russian_flag(BMP *Image);
void color_change(BMP *Image, RGB old, RGB newс);
void Circle(BMP *Image, int radius, int thickness, RGB color, XoY p);
int **circlemask(BMP *Image, int **mask, int radius, XoY p, int n);
void fill_mask(BMP *Image, int ***mask, int x, int y, int target, int replace);

int RGBcmp(RGB color1, RGB color2);
char *check_coordinates(BMP Image, XoY p2, XoY p4);
int color_count(BMP Image, RGB color);

void reverse_x(BMP *Image);
void reverse_y(BMP *Image);
BMP reflect(BMP Image, int axis, int dir, XoY p2, XoY p4);

void copy_and_paste(BMP *Image, XoY p2, XoY p4, XoY newp2);
BMP area_copy(BMP Image, XoY p2, XoY p4);
void area_paste(BMP *Image, BMP copy, XoY newp2);

void clustering(BMP Image, char *path, unsigned int x_parts, unsigned int y_parts);
BMP separating(BMP Image, unsigned int x_parts, unsigned int y_parts, unsigned int thickness, RGB line_color);

BMP collage(BMP Image, unsigned int x_parts, unsigned int y_parts);