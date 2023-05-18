#include "BMP.h"

void InitBMFH(BITMAPFILEHEADER *BMFH, unsigned int W, unsigned int H){
    BMFH->Signature = 0x4D42;
    BMFH->FileSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGB)*W*H;
    BMFH->Reserved1 = 0;
    BMFH->Reserved2 = 0;
    BMFH->FileOffsetToPixelArray = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
}

void InitBMIH(BITMAPINFOHEADER *BMIH, unsigned int W, unsigned int H){
    BMIH->Size = sizeof(BITMAPINFOHEADER);
    BMIH->Width = W;
    BMIH->Height = H;
    BMIH->Planes = 1;
    BMIH->BitsPerPixelCount = 24;
    BMIH->Compression = 0;
    BMIH->ImageSize = 0;
    BMIH->xPixelsPerMeter = 0;
    BMIH->yPixelsPerMeter = 0;
    BMIH->ColorTableSize = 0;
    BMIH->ColorTableImportant = 0;
}   

void InitData(BMP *Image, unsigned int W, unsigned int H){
    Image->data = (RGB**)malloc(sizeof(RGB*)*H);
    for(size_t y = 0; y < H; y++){
        Image->data[y] = (RGB*)malloc(sizeof(RGB)*W);
        for(size_t x = 0; x < W; x++){
            if(y < 333){    
                painting(Image, (RGB){0, 0, 255}, x, y);
            }
            else if(y >= 333 && y < 666){
                painting(Image, (RGB){255, 0, 0}, x, y);
            }
            else{
                painting(Image, (RGB){255, 255, 255}, x, y);
            }
        }
    }
}

BMP InitBMP(unsigned int W, unsigned int H){
    BMP Image;
    InitBMFH(&Image.BMFH, W, H);
    InitBMIH(&Image.BMIH, W, H);
    InitData(&Image, W, H);
    return Image;
}

BMP OpenBMP(const char* path){
    FILE* f = fopen(path, "rb");
    if(f){
        BMP Image;

        fread(&Image.BMFH, sizeof(BITMAPFILEHEADER), 1, f);
        fread(&Image.BMIH, sizeof(BITMAPINFOHEADER), 1, f);

        size_t H = Image.BMIH.Height;
        size_t W = Image.BMIH.Width;
        Image.data = (RGB**)malloc(sizeof(RGB*)*H);
        for(size_t i = 0; i < H; i++){
            Image.data[i] = (RGB*)malloc(sizeof(RGB)*W);
            fread(Image.data[i], sizeof(RGB), W, f);
        }
        fclose(f);
        return Image;
    }
    else{
        puts("Current file is not here");
    }
}

void SaveBMP(const char * path, BMP Image){
    FILE* f = fopen(path, "wb");
    fwrite(&Image.BMFH, sizeof(BITMAPFILEHEADER), 1, f);
    fwrite(&Image.BMIH, sizeof(BITMAPINFOHEADER), 1, f);
    size_t H = Image.BMIH.Height;
    size_t W = Image.BMIH.Width;
    for(size_t y = 0; y < H; y++){
        fwrite(Image.data[y], sizeof(RGB), W, f);
    }
    fclose(f);
}