#include <stdio.h>
#include <stdlib.h>
#include "BMP.h"

int main(){
    BMP Image = InitBMP(998, 998);
    //BMP Image = OpenBMP("a.bmp");
    XoY p2 = {0, 998};
    XoY p4 = {998, 665};
    //Image = reflect(Image, 0, 0, p2, p4, 0);
    //Image = area_cpy(Image, p2, p4, (XoY){0,333}, 1);
    //Image = color_change(Image, (RGB){0, 0, 255}, (RGB){0, 255, 0});
    //printf("%u\n", Image.BMIH.BitsPerPixelCount);
    SaveBMP("image.bmp", Image);
}