#include "BMP.h"

void painting(BMP *Image, RGB Color, unsigned int x, unsigned int y){
    //Applies RGB-data from Color to a pixel in array at (x, y)
    Image->data[y][x].R = Color.R;
    Image->data[y][x].G = Color.G;
    Image->data[y][x].B = Color.B;
}


int RGBcmp(RGB color1, RGB color2){
    //Compares color1 and color2 by their RGB-data
    if(color1.R == color2.R && color1.G == color2.G && color1.B == color2.B){
        return 1;
    }
    return 0;
}

char *check_coordinates(BMP Image, XoY p2, XoY p4){
    if(p2.x >= Image.BMIH.Width || p2.x < 0){
        return "x coordinate of first point p2 is out of resolution";
    }
    if(p2.y >= Image.BMIH.Height || p2.y < 0){
        return "y coordinate of first point p2 is out of resolution";
    }
    if(p4.x >= Image.BMIH.Width || p4.x < 0){
        return "x coordinate of second point p4 is out of resolution";
    }
    if(p4.y >= Image.BMIH.Height || p4.y < 0){
        return "y coordinate of second point p4 is out of resolution";
    }
    return NULL;
}

BMP reflect(BMP Image, int axis, int dir, XoY p2, XoY p4, int security){
    if(check_coordinates(Image, p2, p4)){
        printf("%s\n", check_coordinates(Image, p2, p4));
        return Image;
    }
    XoY p1 = {p4.x, p2.y};
    XoY p3 = {p2.x, p4.y};

    if(axis == 0){
        if(security == 1){
            if(p4.y-1 < 0 || p3.y-1 < 0 || 2*p3.y - p2.y - 1 < 0 || 2*p1.y + p4.y + 1 >= Image.BMIH.Height || p2.y+1 >= Image.BMIH.Height || p1.y+1 >= Image.BMIH.Height){
                puts("Area with entered coordinates is too big and cannot be reflected on both sides\nIf you want to reflect it partially, use security = 0");
                return Image;
            }
        }
        else if(security != 0){
            puts("Incorrect security value");
            return Image;
        }
        if(dir == 0){
            XoY newp1 = {p4.x, p4.y-1};
            XoY newp2 = {p2.x, p3.y-1};
            XoY newp3 = {p3.x, 2*p3.y - p2.y - 1};
            XoY newp4 = {p4.x, newp3.y};
            if(newp1.y < 0 || newp2.y < 0 || newp3.y < 0){
                puts("Attention: reflected area of image is partially out of resolution, the result will be cropped");
            }
            for(int y = p3.y, new_y = newp2.y; y <= p2.y && new_y >= newp3.y; y++, new_y--){
                if(new_y < 0){
                        break;
                    }
                for(int x = p3.x; x <= p4.x; x++){
                    Image.data[new_y][x] = Image.data[y][x];
                }
            }
        }
        else if(dir == 1){
            XoY newp1 = {p1.x, 2*p1.y + p4.y + 1};
            XoY newp2 = {p2.x, newp1.y};
            XoY newp3 = {p3.x, p2.y+1};
            XoY newp4 = {p4.x, p1.y+1};
            if(newp1.y >= Image.BMIH.Height || newp3.y >= Image.BMIH.Height || newp4.y >= Image.BMIH.Height){
                puts("Attention: reflected area of image is partially out of resolution, the result will be cropped");
            }
            for(int y = p2.y, new_y = newp3.y; y >= p3.y && new_y <= newp2.y; y--, new_y++){
                if(new_y >= Image.BMIH.Height){
                        break;
                    }
                for(int x = p2.x; x <= p1.x; x++){
                    Image.data[new_y][x] = Image.data[y][x];
                }
            }
        }
        else{
            puts("Incorrect dir value");
        }
    }
    else if(axis == 1){
        if(security){
            if(p2.x-1 < 0 || 2*p2.x - p1.x - 1 < 0 || p3.x-1 < 0 || 2*p1.x - p2.x + 1 >= Image.BMIH.Width || p1.x+1 >= Image.BMIH.Width || p4.x+1 >= Image.BMIH.Width){
                puts("Area with entered coordinates is too big and cannot be reflected on both sides\nIf you want to reflect it partially, use security = 0");
                return Image;
            }
        }
        else if(security != 0){
            puts("Incorrect security value");
            return Image;
        }
        else if(dir == 0){ 
            XoY newp1 = {p2.x-1, p1.y};
            XoY newp2 = {2*p2.x - p1.x - 1, p2.y};
            XoY newp3 = {newp2.x, p3.y};
            XoY newp4 = {p3.x-1, p4.y};
            if(newp1.x < 0 || newp2.x < 0 || newp4.x < 0){
                puts("Attention: reflected area of image is partially out of resolution, the result will be cropped");
            }
            for(int x = p2.x, new_x = newp1.x; x <= p1.x && new_x >= newp2.x; x++, new_x--){
                if(new_x < 0){
                        break;
                    }
                for(int y = p2.y; y >= p3.y; y--){
                    Image.data[y][new_x] = Image.data[y][x];
                }
            }
        }
        else if(dir == 1){
            XoY newp1 = {2*p1.x - p2.x + 1, p1.y};
            XoY newp2 = {p1.x+1, p2.y};
            XoY newp3 = {p4.x+1, p3.y};
            XoY newp4 = {newp1.x, p4.y};
            if(newp1.x >= Image.BMIH.Width || newp2.x >= Image.BMIH.Width || newp3.x >= Image.BMIH.Width){
                puts("Attention: reflected area of image is partially out of resolution, the result will be cropped");
            }
            for(int x = p1.x, new_x = newp2.x; x >= p2.x && new_x <= newp1.x; x--, new_x++){
                if(new_x >= Image.BMIH.Height){
                        break;
                    }
                for(int y = p2.y; y >= p3.y; y--){
                    Image.data[y][new_x] = Image.data[y][x];
                }
            }
        }
        else{
            puts("Incorrect dir value");
        }
    }
    else{
        puts("Incorrect axis value");
    }
    return Image;
}

BMP area_cpy(BMP Image, XoY p2, XoY p4, XoY newp2, int security){
    if(check_coordinates(Image, p2, p4)){
        return Image;
    }
    XoY newp4 = {newp2.x + (p4.x - p2.x), newp2.y - (p2.y - p4.y)};

    XoY p1 = {p4.x, p2.y};
    XoY p3 = {p2.x, p4.y};

    XoY newp1 = {newp4.x, newp2.y};
    XoY newp3 = {newp2.x, newp4.y};

    if(security == 1){
        if(newp2.x < 0 || newp2.x >= Image.BMIH.Width){
            puts("x coordinate of new point newp2 is out of resolution\nIf you want to paste a cropped area, use security = 0");
            return Image;
        }
        if(newp2.y < 0 || newp2.y >= Image.BMIH.Height){
            puts("y coordinate of new point newp2 is out of resolution\nIf you want to paste a cropped area, use security = 0");
            return Image;
        }
        if(newp4.x >= Image.BMIH.Width || newp4.y < 0){ 
            puts("Area with entered coordinates cannot be pasted there\nIf you want to paste a cropped area, use security = 0");
        }
    }
    else if(security != 0){
        puts("Incorrect security value");
    }

    for(int y = p2.y, new_y = newp2.y; y >= p3.y && new_y >= newp3.y; y--, new_y--){
        for(int x = p2.x; x <= p4.x; x++){
            if(x < 0 || x >= Image.BMIH.Width){
                continue;
            }
            Image.data[new_y][x] = Image.data[y][x];
        }
    }
    return Image;
}

BMP color_change(BMP Image, RGB old, RGB new){
    for(int y = 0; y < Image.BMIH.Height; y++){
        for(int x = 0; x < Image.BMIH.Width; x++){
            if(RGBcmp(Image.data[y][x], old)){
                Image.data[y][x] = new;
            }
        }
    }
    return Image;
}

int color_count(BMP Image, RGB color){
    int res = 0;
    for(int y = 0; y < Image.BMIH.Height; y++){
        for(int x = 0; x < Image.BMIH.Width; x++){
            if(RGBcmp(color, Image.data[y][x])){
                res++;
            }
        }
    }
    return res;
}