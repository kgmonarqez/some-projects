#include "BMP.h"

RGB **InitData(int W, int H){
    unsigned int W_data = sizeof(RGB)*W;
    while(W_data%4){
        W_data++;
    }
    RGB **data = (RGB**)malloc(sizeof(RGB*)*H);
    for(size_t y = 0; y < H; y++){
        data[y] = (RGB*)malloc(W_data);
    }
    return data;
}

BMP InitBMP(int W, int H){
    BMP Image ;
    unsigned int W_data = sizeof(RGB)*W;
    while(W_data%4){
        W_data++;
    }

    Image.BMFH.Signature = 0x4D42;
    Image.BMFH.FileSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + W_data*H;
    Image.BMFH.Reserved1 = 0;
    Image.BMFH.Reserved2 = 0;
    Image.BMFH.FileOffsetToPixelArray = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    Image.BMIH.Size = sizeof(BITMAPINFOHEADER);
    Image.BMIH.Width = W;
    Image.BMIH.Height = H;
    Image.BMIH.Planes = 1;
    Image.BMIH.BitsPerPixelCount = 24;
    Image.BMIH.Compression = 0;
    Image.BMIH.ImageSize = 0;
    Image.BMIH.xPixelsPerMeter = 0;
    Image.BMIH.yPixelsPerMeter = 0;
    Image.BMIH.ColorTableSize = 0;
    Image.BMIH.ColorTableImportant = 0;

    Image.data = InitData(W, H);

    return Image;
}

BMP OpenBMP(const char* path){
    FILE* f = fopen(path, "rb");
    BMP Image;
    if(f){
        BITMAPFILEHEADER BMFH;
        BITMAPINFOHEADER BMIH;
        fread(&BMFH, sizeof(BITMAPFILEHEADER), 1, f);
        fread(&BMIH, sizeof(BITMAPINFOHEADER), 1, f);

        if(!(BMFH.Signature == 0x4D42 || BMFH.Signature == 0x424D)){
            puts("Incorrect file type");
            exit(0);
        }
        if(BMIH.Size != sizeof(BITMAPINFOHEADER)){
            puts("BMP version of this image is not supported");
            exit(0);
        }
        if(BMIH.BitsPerPixelCount != 24){
            puts("The number of bits per pixel of this image doesn't equal 24");
            exit(0);
        }
        if(BMIH.Compression){
            puts("Compression of this image is not supporrted");
        }

        Image.BMFH = BMFH;
        Image.BMIH = BMIH;

        int H = abs(Image.BMIH.Height);
        int W = Image.BMIH.Width;
        unsigned int W_data = (Image.BMFH.FileSize - sizeof(BITMAPINFOHEADER) - sizeof(BITMAPFILEHEADER))/H;

        Image.data = (RGB**)malloc(sizeof(RGB*)*H);
        for(size_t i = 0; i < H; i++){
            Image.data[i] = (RGB*)malloc(W_data);
            fread(Image.data[i], 1, W_data, f);
        }

        fclose(f);
    }
    else{
        puts("Wrong path to the file");
        exit(0);
    }
    return Image;
}

void SaveBMP(const char *path, BMP Image){
    FILE* f = fopen(path, "wb");
    if(f){
        fwrite(&Image.BMFH, sizeof(BITMAPFILEHEADER), 1, f);
        fwrite(&Image.BMIH, sizeof(BITMAPINFOHEADER), 1, f);
        int H = abs(Image.BMIH.Height);
        int W = Image.BMIH.Width;
        unsigned int W_data = (Image.BMFH.FileSize - sizeof(BITMAPINFOHEADER) - sizeof(BITMAPFILEHEADER))/H;
        for(int y = 0; y < H; y++){
            fwrite(Image.data[y], 1, W_data, f);
        }
        fclose(f);
    }
    else{
        puts("Wrong path for saving");
        exit(0);
    }
}

void data_free(BMP *Image){
    for(int y = 0; y < Image->BMIH.Height; y++){
        free(Image->data[y]);
    }
    free(Image->data);
}