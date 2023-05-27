#include "BMP.h"

void painting(BMP *Image, RGB Color, int x, int y){
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
        return "x coordinate of the first point is out of resolution";
    }
    if(p2.y >= Image.BMIH.Height || p2.y < 0){
        return "y coordinate of the first point is out of resolution";
    }
    if(p4.x >= Image.BMIH.Width || p4.x < 0){
        return "x coordinate of the second point is out of resolution";
    }
    if(p4.y >= Image.BMIH.Height || p4.y < 0){
        return "y coordinate of the second point is out of resolution";
    }
    return NULL;
}

void reverse_x(BMP *Image){
    int H = Image->BMIH.Height;
    int W = Image->BMIH.Width;
    RGB **r_data = InitData(W, H);
    for(int y = 0; y < H; y++){
        for(int new_x = 0, old_x = W-1; new_x < W && old_x >= 0; new_x++, old_x--){
            r_data[y][new_x] = Image->data[y][old_x];
        }
    }
    data_free(Image);
    Image->data = r_data; 
}

void reverse_y(BMP *Image){
    int H = Image->BMIH.Height;
    int W = Image->BMIH.Width;
    RGB **r_data = (RGB**)malloc(sizeof(RGB*)*H);
    for(int new_y = 0, old_y = H-1; new_y < H && old_y >= 0; new_y++, old_y--){
        r_data[new_y] = Image->data[old_y];
    }
    free(Image->data);
    Image->data = r_data;
}

BMP reflect(BMP Image, int axis, int vector, XoY p2, XoY p4){
    BMP reflected_area;
    char *message;
    if(message = check_coordinates(Image, p2, p4)){
        printf("--reflect: %s\n", check_coordinates(Image, p2, p4));
        exit(0);
    }
    XoY newp2;
    XoY newp4;
    if(axis == X){
        if(vector == DOWN){
            newp2 = (XoY){p2.x, p4.y-1};
            newp4 = (XoY){p4.x, 2*p4.y - p2.y - 1};
            if(newp4.y < 0){
                puts("--reflect attention: reflected area of image is partially out of resolution, the result will be cropped");
            }
        }
        else if(vector == UP){
            newp2 = (XoY){p2.x, 2*p2.y - p4.y + 1};
            newp4 = (XoY){p4.x, p2.y+1};
            if(newp2.y >= Image.BMIH.Height){
                puts("--reflect attention: reflected area of image is partially out of resolution, the result will be cropped");
            }
        }
        reflected_area = area_copy(Image, p2, p4);
        reverse_y(&reflected_area);
        area_paste(&Image, reflected_area, newp2);
    }
    else if(axis == Y){
        if(vector == LEFT){ 
            newp2 = (XoY){2*p2.x - p4.x - 1, p2.y};
            newp4 = (XoY){p2.x-1, p4.y};
            if(newp2.x < 0){
                puts("--reflect: reflected area of image is partially out of resolution, the result will be cropped");
            }
        }
        else if(vector == RIGHT){
            newp2 = (XoY){p4.x+1, p2.y};
            newp4 = (XoY){2*p4.x - p2.x + 1, p4.y};
            if(newp4.x >= Image.BMIH.Width){
                puts("--reflect: reflected area of image is partially out of resolution, the result will be cropped");
            }
        }
        reflected_area = area_copy(Image, p2, p4);
        reverse_x(&reflected_area);
        area_paste(&Image, reflected_area, newp2);
    }
    data_free(&reflected_area);
    return Image;
}

void copy_and_paste(BMP *Image, XoY p2, XoY p4, XoY newp2){
    char *message;
    if(message = check_coordinates(*Image, p2, p4)){
        printf("--copy-and-paste: %s\n", message);
        exit(0);
    }
    BMP copy = area_copy(*Image, p2, p4);
    XoY newp4 = {newp2.x + (copy.BMIH.Width - 1), newp2.y - (copy.BMIH.Height - 1)};
    if(newp2.x < 0 || newp4.x >= Image->BMIH.Width || newp2.y >= Image->BMIH.Height || newp4.y < 0){
        puts("--copy-and-paste: selected area of image is partially out of resolution, the result will be cropped");
    }
    area_paste(Image, copy, newp2);
    data_free(&copy);
}

BMP area_copy(BMP Image, XoY p2, XoY p4){
    char *message;  
    if(message = check_coordinates(Image, p2, p4)){
        printf("--crop: %s\n", check_coordinates(Image, p2, p4));
        exit(0);
    }
    int area_H = p2.y - p4.y + 1; 
    int area_W = p4.x - p2.x + 1;
    BMP copy = InitBMP(area_W, area_H);
    for(int y = p4.y, cpy_y = 0; y <= p2.y; y++, cpy_y++){
        for(int x = p2.x, cpy_x = 0; x <= p4.x; x++, cpy_x++){
            copy.data[cpy_y][cpy_x] = Image.data[y][x];
        }
    }
    return copy;
}

void area_paste(BMP *Image, BMP copy, XoY newp2){
    XoY newp4 = {newp2.x + (copy.BMIH.Width - 1), newp2.y - (copy.BMIH.Height - 1)};
    for(int y = newp4.y, cpd_y = 0; cpd_y < copy.BMIH.Height; y++, cpd_y++){
        if(y < 0 || y >= Image->BMIH.Height){
            continue;
        }
        for(int x = newp2.x, cpd_x = 0; cpd_x < copy.BMIH.Width; x++, cpd_x++){
            if(x < 0 || x >= Image->BMIH.Width){
                continue;
            }
            Image->data[y][x] = copy.data[cpd_y][cpd_x];
        }
    }
}

void color_change(BMP *Image, RGB old, RGB newс){
    int replaced_pixels = 0;
    for(int y = 0; y < Image->BMIH.Height; y++){
        for(int x = 0; x < Image->BMIH.Width; x++){
            if(RGBcmp(Image->data[y][x], old)){
                Image->data[y][x] = newс;
                replaced_pixels++;
            }
        }
    }
    if(replaced_pixels){
        printf("Pixels with changed color: %d\n", replaced_pixels);
    }
    else{
        puts("No pixels with entered color found");
    }
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

void Russian_flag(BMP *Image){
    int H = abs(Image->BMIH.Height);
    int W = Image->BMIH.Width;
    for(int y = 0; y < H; y++){
        for(int x = 0; x < W; x++){
            if(y < H/3){    
                painting(Image, (RGB){0, 0, 255}, x, y);
            }
            else if(y >= H/3 && y < H*2/3){
                painting(Image, (RGB){255, 0, 0}, x, y);
            }
            else{
                painting(Image, (RGB){255, 255, 255}, x, y);
            }
        }
    }
}

void clustering(BMP Image, char *path, unsigned int x_parts, unsigned int y_parts){
    DIR *dir = opendir(path);
    if(dir){
        if(!(x_parts > Image.BMIH.Width || y_parts > Image.BMIH.Height)){
            int W = Image.BMIH.Width;
            int H = abs(Image.BMIH.Height);
            int k = 0;
            int q = 1;
            int prod = x_parts*y_parts;
            while(prod%10){
                k++;
                prod/=10;
            }
            char nums[strlen(path) + k + 5];
            for(int i = 1; i <= y_parts; i++){
                for(int j = 1; j <= x_parts; j++){
                    XoY p2 = {W*(j - 1)/x_parts, H*i/y_parts - 1};
                    XoY p4 = {W*j/x_parts - 1, H*(i - 1)/y_parts};
                    BMP part = area_copy(Image, p2, p4);
                    sprintf(nums, "%s/%d.bmp", path, q++);
                    SaveBMP(nums, part);
                }
            }
        }
        else{
            puts("--clustering: cannot separate image in so many parts");
            exit(0);
        }
    }
    else{
        puts("--clustering: wrong path to the directory");
        exit(0);
    }
}

int **pastemask(int **mask, XoY p2, XoY p4){
    for(int y = p4.y; y <= p2.y; y++){
        for(int x = p2.x; x <= p4.x; x++){
            mask[y][x] = 1;
        }
    }
    return mask;
}

BMP separating(BMP Image, unsigned int x_parts, unsigned int y_parts, unsigned int thickness, RGB line_color){
    if(x_parts > Image.BMIH.Width || y_parts > Image.BMIH.Height){
        puts("--separating: cannot separate image in so many parts");
        exit(0);
    }
    int W = Image.BMIH.Width;
    int H = abs(Image.BMIH.Height);
    BMP sep_image = InitBMP(W + (x_parts - 1)*thickness, H + (y_parts - 1)*thickness);
    int **mask = (int**)malloc(sizeof(int*)*sep_image.BMIH.Height);
    for(int i = 0; i < sep_image.BMIH.Height; i++){
        mask[i] = (int*)calloc(sep_image.BMIH.Width, sizeof(int));
    }
    for(int i = 1; i <= y_parts; i++){
        for(int j = 1; j <= x_parts; j++){
            XoY p2 = {W*(j - 1)/x_parts, H*i/y_parts - 1};
            XoY p4 = {W*j/x_parts - 1, H*(i - 1)/y_parts};
            BMP part = area_copy(Image, p2, p4);
            XoY newp2 = {p2.x + thickness*(j - 1), p2.y + thickness*(i - 1)}; 
            XoY newp4 = {newp2.x + (part.BMIH.Width - 1), newp2.y - (part.BMIH.Height - 1)};
            area_paste(&sep_image, part, newp2);
            mask = pastemask(mask, newp2, newp4);
        }
    }
    for(int y = 0; y < sep_image.BMIH.Height; y++){
        for(int x = 0; x < sep_image.BMIH.Width; x++){
            if(!mask[y][x]){
                painting(&sep_image, line_color, x, y);
            }
        }
    }
    data_free(&Image);
    return sep_image;
}

void Circle(BMP *Image, int radius, int thickness, RGB color, XoY p){
    int **mask = (int**)malloc(sizeof(int*)*Image->BMIH.Height);
    for(int i = 0; i < Image->BMIH.Height; i++){
        mask[i] = (int*)calloc(Image->BMIH.Width, sizeof(int));
    }
    mask = circlemask(Image, mask, radius, p, 1);
    int new_radius = radius - thickness + 1;
    if(thickness == 2 || thickness == 3){
        fill_mask(Image, &mask, p.x, p.y, 0, 1);
        mask = circlemask(Image, mask, new_radius, p, 0);
        fill_mask(Image, &mask, p.x, p.y, 1, 0);
        mask = circlemask(Image, mask, new_radius, p, 0);
    }
    else if(thickness > 3){
        mask = circlemask(Image, mask, new_radius, p, 1);
        fill_mask(Image, &mask, p.x + new_radius + 1, p.y, 0, 1);
    }
    for(int y = 0; y < Image->BMIH.Height; y++){
        for(int x = 0; x < Image->BMIH.Width; x++){
            if(mask[y][x] == 1){
                painting(Image, color, x, y);
            }
        }
    }
    for(int i = 0; i < Image->BMIH.Height; i++){
        free(mask[i]);
    }
    free(mask);
}

int **circlemask(BMP *Image, int **mask, int radius, XoY p, int n){
    int x = radius;
    int y = 0;
    int x0 = p.x;
    int y0 = p.y;
    int radiusError = 1 - x;
    int W = Image->BMIH.Width;
    int H = abs(Image->BMIH.Height);
    while (x >= y){
        if(x + y0 >= 0 && x + y0 < H && y + x0 >= 0 && y + x0 < W){
            mask[x + y0][y + x0] = n;
        }
        else{puts("--draw-circle: circle is out if image"); exit(0);}
        if(y + y0 >= 0 && y + y0 < H && x + x0 >= 0 && x + x0 < W){
            mask[y + y0][x + x0] = n;
        }
        else{puts("--draw-circle: circle is out if image"); exit(0);}
        if(-x + y0 >= 0 && -x + y0 < H && y + x0 >= 0 && y + x0 < W){
            mask[-x + y0][y + x0] = n;
        }
        else{puts("--draw-circle: circle is out if image"); exit(0);}
        if(-y + y0 >= 0 && -y + y0 < H && x + x0 >= 0 && x + x0 < W){
            mask[-y + y0][x + x0] = n;
        }
        else{puts("--draw-circle: circle is out if image"); exit(0);}
        if(-x + y0 >= 0 && -x + y0 < H && -y + x0 >= 0 && -y + x0 < W){
            mask[-x + y0][-y + x0] = n;
        }
        else{puts("--draw-circle: circle is out if image"); exit(0);}
        if(-y + y0 >= 0 && -y + y0 < H && -x + x0 >= 0 && -x + x0 < W){
            mask[-y + y0][-x + x0] = n;
        }
        else{puts("--draw-circle: circle is out if image"); exit(0);}
        if(x + y0 >= 0 && x + y0 < H && -y + x0 >= 0 && -y + x0 < W){
            mask[x + y0][-y + x0] = n;
        }
        else{puts("--draw-circle: circle is out if image"); exit(0);}
        if(y + y0 >= 0 && y + y0 < H && -x + x0 >= 0 && -x + x0 < W){
            mask[y + y0][-x + x0] = n;
        }
        else{puts("--draw-circle: circle is out if image"); exit(0);}
        y++;
        if (radiusError < 0){
            radiusError += 2 * y + 1;
        }
        else{
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
    return mask;
}

void fill_mask(BMP *Image, int ***mask, int x, int y, int target, int replace){
    (*mask)[y][x] = replace;
    if(x - 1 >= 0 && (*mask)[y][x - 1] == target){
        fill_mask(Image, mask, x - 1, y, target, replace);
    }
    if(x + 1 < Image->BMIH.Width && (*mask)[y][x + 1] == target){
        fill_mask(Image, mask, x + 1, y, target, replace);
    }
    if(y - 1 >= 0 && (*mask)[y - 1][x] == target){
        fill_mask(Image, mask, x, y - 1, target, replace);
    }
    if(y + 1 < abs(Image->BMIH.Height) && (*mask)[y + 1][x] == target){
        fill_mask(Image, mask, x, y + 1, target, replace);
    }
}

BMP collage(BMP Image, unsigned int x_parts, unsigned int y_parts){
    BMP collage = InitBMP(Image.BMIH.Width*x_parts, abs(Image.BMIH.Height)*y_parts);
    int W = collage.BMIH.Width;
    int H = abs(collage.BMIH.Height);
    for(int i = 1; i <= y_parts; i++){
        for(int j = 1; j <= x_parts; j++){
            XoY p2 = {W*(j - 1)/x_parts, H*i/y_parts - 1};
            area_paste(&collage, Image, p2);
        }
    }
    return collage;
}