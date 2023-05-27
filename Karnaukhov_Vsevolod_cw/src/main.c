#include <stdio.h>
#include <getopt.h>
#include "BMP.h"
#include <ctype.h>

int isNum(char *string){
    for(int i = 0; i < strlen(string); i++){
        if(!isalnum(string[i])){
            return 0;
        }
    }
    return 1;
}

XoY read_coordinates(char *name){
    char *data;
    char *n;
    XoY p;
    data = malloc(sizeof(char)*strlen(optarg));
    data = strcpy(data, optarg);
    n = strtok(data, ",");
    if(n && isNum(n)){
        p.x = atoi(n);
    }
    else{
        printf("In %s: incorrect values type (first-point/second-point). They must be integers\n", name);
        exit(0);
    }
    n = strtok(NULL, ",");
    if(n && isNum(n)){
        p.y = atoi(n);
    }
    else{
        printf("In %s: incorrect values type (first-point/second-point). They must be integers\n", name);
        exit(0);
    }
    free(data);
    return p;
}

RGB read_color(char *name){
    char *data;
    char *n;
    RGB color;
    data = malloc(sizeof(char)*strlen(optarg));
    data = strcpy(data, optarg);
    n = strtok(data, ",");
    if(n && isNum(n) && atoi(n) >= 0 && atoi(n) <= 255){
        color.R = atoi(n);
    }
    else{
        printf("In %s: incorrect values type or meaning (color/desired-color, R). It must be integer and be between 0 and 255 inclusive", name);
        exit(0);
    }
    n = strtok(NULL, ",");
    if(n && isNum(n) && atoi(n) >= 0 && atoi(n) <= 255){
        color.G = atoi(n);
    }
    else{
        printf("In %s: incorrect values type or meaning (color/desired-color, G). It must be integer and be between 0 and 255 inclusive", name);
        exit(0);
    }
    n = strtok(NULL, ",");
    if(n && isNum(n) && atoi(n) >= 0 && atoi(n) <= 255){
        color.B = atoi(n);
    }
    else{
        printf("In %s: incorrect values type or meaning (color/desired-color, B). It must be integer and be between 0 and 255 inclusive", name);
        exit(0);
    }
    free(data);
    return color;
}

void printinfo(BMP Image){
    puts("\n'''Image resolution info'''\n");
    printf("# Width:          %d\n", Image.BMIH.Width);
    printf("# Height:         %d\n", Image.BMIH.Height);
    printf("# Pixel depth:    %d\n\n", Image.BMIH.BitsPerPixelCount);
    puts("'''BMP info'''\n");
    printf("# Signature:      0x%x\n", Image.BMFH.Signature);
    printf("# File size:      %d\n", Image.BMFH.FileSize);
    printf("# File offset\n");
    printf("  to pixel array: %d\n", Image.BMFH.FileOffsetToPixelArray);
    printf("# BMIH version:   %d\n", Image.BMIH.Size);
    printf("# Planes:         %d\n", Image.BMIH.Planes);
    printf("# Compression:    %d\n", Image.BMIH.Compression);
    printf("# Image size:     %d\n", Image.BMIH.ImageSize);
    printf("# Pixels\n");
    printf("  per meter:\n");
    printf("      x:          %d\n", Image.BMIH.xPixelsPerMeter);
    printf("      y:          %d\n", Image.BMIH.yPixelsPerMeter);
    printf("# Color table:\n");
    printf("      Size:       %d\n", Image.BMIH.ColorTableSize);
    printf("      Important:  %d\n", Image.BMIH.ColorTableImportant);
}

void printhelp(){
    puts("////////////////////////////////////////////////");
    puts("'''Opening, initiating, saving and image info'''");
    puts("////////////////////////////////////////////////");
    puts("# --init-bmp/-M {Initiates an empty black area with size of entered resolution}:");
    puts("\t--width/-w {width of the image (integer, > 0)}");
    puts("\t--height/-h {height of the image (integer, > 0)}");
    puts("\tExample: --init-bmp -w 100 -h 100\n");
    puts("# --open/-Z {Opens an image of BMP format. This program supports only images with BITMAPINFOHEADER V3}:");
    puts("\tThis function accepts a path to the image");
    puts("\tExample: --open ./.../image.bmp\n");
    puts("# --save/-S {Saves the image in the entered path}:");
    puts("\tThis function accepts the path with name where to save the image");
    puts("\tExample: --save ./.../image.bmp\n");
    puts("# --info/-I {Shows the information about BMP image}");
    puts("////////////////////////////////");
    puts("'''Image processing functions'''");
    puts("////////////////////////////////");
    puts("# --reverse-y/-Y {Reverses the image by Y axis}\n");
    puts("# --reverse-x/-X {Reverses the image by X axis}\n");
    puts("# --reflect/-R {Reflects the area with entered coordinates by axis against chosen vector}:");
    puts("\t--axis/-a {Axis on which the image is reflected ('x'/'y')}");
    puts("\t--vector/-v {Direction vector of image reflection (if axis = 'y': 'left'/'right', if axis = 'x': 'down'/'up')}");
    puts("\t--first-point/-f {Coordinates of the top left point of area (regular expression: 'x,y', x,y - integers, > 0)}");
    puts("\t--second-point/-s {Coordinates of the bottom right point of area (regular expression: 'x,y', x,y - integers, > 0)}");
    puts("\tExample: --reflect -a x -v up -f 238,54 -s 300,0\n");
    puts("# --copy-and-paste/-P {Makes a copy of the image's area and pastes it on entered coordinates}:");
    puts("\t--first-point/-f {Coordinates of the top left point of area (regular expression: 'x,y', x,y - integers, > 0)}");
    puts("\t--second-point/-s {Coordinates of the bottom right point of area (regular expression: 'x,y', x,y - integers, > 0)}");
    puts("\t--new-point/-n {New coordinates of the top left point of area (regular expression: 'x,y', x,y - integers, > 0)}");
    puts("\tExample: --reflect -a x -v up -f 238,54 -s 300,0 -n 0,500\n");
    puts("# --crop/-Q {Crops an area of the image}:");
    puts("\t--first-point/-f {Coordinates of the top left point of area (regular expression: 'x,y', x,y - integers, > 0)}");
    puts("\t--second-point/-s {Coordinates of the bottom right point of area (regular expression: 'x,y', x,y - integers, > 0)}");
    puts("\tExample: --crop -f 384,55 -s 500,0\n");
    puts("# --color-change/-C {Changes color of each pixel which contains desired pixel to the entered color}:");
    puts("\t--desired-color/-d {The color which is desired in the image (Regular expression: 'R,G,B', R,G,B - integers, 0 <= R,G,B <= 255)}");
    puts("\t--color/-c {The color that replaces the desired color (Regular expression: 'R,G,B', R,G,B - integers, 0 <= R,G,B <= 255)}");
    puts("\tExample: --change-color -d 0,0,0 -c 255,0,0\n");
    puts("# --color-count/-N {Counts the number of desired color}:");
    puts("\t--color/-c {The color which is desired in the image (Regular expression: 'R,G,B', R,G,B - integers, 0 <= R,G,B <= 255)}");
    puts("\tExample: --color-count -c 0,0,0\n");
    puts("# --clustering/-G {Separates the image into N*M parts into separate files}:");
    puts("\t--path/-o {Path where to save parts}");
    puts("\t--x-parts/-x {Number of parts on X axis (integer, > 0 and <= image width)}");
    puts("\t--y-parts/-y {Number of parts on Y axis (integer, > 0 and <= image height)}");
    puts("\tExample: --clustering -x 5 -y 5\n");
    puts("# --separating/-T {Separates the image into N*M parts by lines with entered color}:");
    puts("\t--x-parts/-x {Number of parts on X axis (integer, > 0 and <= image width)}");
    puts("\t--y-parts/-y {Number of parts on Y axis (integer, > 0 and <= image height)}");
    puts("\t--thickness/-t {Thickness of the dividing line in pixels (Integer, > 0)}");
    puts("\t--color/-c {The color of the dividing line (Regular expression: 'R,G,B', R,G,B - integers, 0 <= R,G,B <= 255)}");
    puts("\tExample: --separating -x 5 -y 5 -t 10 -c 255,0,0\n");
    puts("# --draw-circle/-O {Draws circle around entered point}:");
    puts("\t--radius/-r {Radius of th circle (integer, > 0)}");
    puts("\t--thickness/-t {Thickness of the circle line (Integer, > 0)}");
    puts("\t--color/-c {Color of the circle line (Regular expression: 'R,G,B', R,G,B - integers, 0 <= R,G,B <= 255)}");
    puts("\t--point/-p {Coordinates of the center of the circle (regular expression: 'x,y', x,y - integers, > 0)}");
    puts("\tExample: --draw-circle -r 10 -t 5 -c 255,0,0 -p 234,10\n");
    puts("# --collage/-L {Makes a collage of the image}:");
    puts("\t--x-parts/-x {Number of parts on X axis (integer, > 0 and <= image width)}");
    puts("\t--y-parts/-y {Number of parts on Y axis (integer, > 0 and <= image height)}");
    puts("\tExample: --collage -x 5 -y 5\n");
}

int main(int argc, char *argv[]){
    BMP Image;
    struct option a[] = {
        //functions:
        {"help", no_argument, NULL, 'H'},
        {"init", no_argument, NULL, 'M'},
        {"open", required_argument, NULL, 'Z'},
        {"save", required_argument, NULL, 'S'},
        {"info", no_argument, NULL, 'I'},
        {"reverse-y", no_argument, NULL, 'Y'},
        {"reverse-x", no_argument, NULL, 'X'},
        {"reflect", no_argument, NULL, 'R'},
        {"copy-and-paste", no_argument, NULL, 'P'},
        {"crop", no_argument, NULL, 'Q'},
        {"color-change", no_argument, NULL, 'C'},
        {"color-count", required_argument, NULL, 'N'},
        {"clustering", no_argument, NULL, 'G'},
        {"separating", no_argument, NULL, 'T'},
        {"draw-circle", no_argument, NULL, 'O'},
        {"collage", no_argument, NULL, 'L'},
        //variables:
        {"width", required_argument, NULL, 'w'},
        {"height", required_argument, NULL, 'h'},
        {"axis", required_argument, NULL, 'a'},
        {"vector", required_argument, NULL, 'v'},
        {"first-point", required_argument, NULL, 'f'},
        {"second-point", required_argument, NULL, 's'},
        {"new-point", required_argument, NULL, 'n'},
        {"point", required_argument, NULL, 'p'},
        {"path", required_argument, NULL, 'o'},
        {"color", required_argument, NULL, 'c'},
        {"desired-color", required_argument, NULL, 'd'},
        {"x-parts", required_argument, NULL, 'x'},
        {"y-parts", required_argument, NULL, 'y'},
        {"thickness", required_argument, NULL, 't'},
        {"radius", required_argument, NULL, 'r'},
    };
    char *func_opts = "HMZ:S:IYXRPQCN:GTOLw:h:a:v:f:s:n:p:o:c:d:x:y:t:r:";
    char *var_opts = "w:h:a:v:f:s:n:p:o:c:d:x:y:t:r:";
    int input = getopt_long(argc, argv, func_opts, a, NULL);
    if(input == 'H'){
        printhelp();
        exit(0);
    }
    if(input != 'A' && input != 'Z'){
        puts("No file opened or created\nUse -H/--help for program manual");
        exit(0);
    }

    int W, H, x_parts, y_parts, thickness, radius;
    int axis, vector;
    XoY p2, p4, newp2, p;
    RGB old, newc, color;
    char *path;

    while(input != -1){
        switch(input){
            case 'M':
                int W, H;
                for(int var_count = 1; var_count <= 2; var_count++){
                    if((input = getopt_long(argc, argv, var_opts, a, NULL)) == -1){
                        puts("Not enough variables");
                        exit(0);
                    }
                    switch(input){
                        case 'w': 
                            if(isNum(optarg) && atoi(optarg) > 0){
                                W = atoi(optarg);
                            }
                            else{
                                puts("In --init-bmp: incorrect values type or meaning (width). This must be an integer");
                                exit(0);
                            }
                            break;
                        case 'h':
                            if(isNum(optarg) && atoi(optarg) > 0){
                                H = atoi(optarg);
                            }
                            else{
                                puts("In --init-bmp: incorrect values type or meaning (height). This must be an integer");
                                exit(0);
                            }
                            break;
                        case '?': puts("--init: wrong flags used or not enough variables"); exit(0);
                    }
                }
                Image = InitBMP(W, H);
                break;
            case 'Z':
                Image = OpenBMP(optarg);
                break;
            case 'S':
                SaveBMP(optarg, Image);
                break;
            case 'I':
                printinfo(Image);
                break;
            case 'Y':
                reverse_y(&Image);
                break;
            case 'X':
                reverse_x(&Image);
                break;
            case 'R':
                for(int var_count = 1; var_count <= 4; var_count++){
                    if((input = getopt_long(argc, argv, "", a, NULL)) == -1){
                        puts("Not enough variables");
                        exit(0);
                    }
                    switch(input){
                        case 'a':
                            if(!strcmp(optarg, "x")){
                                axis = X;
                            }
                            else if(!strcmp(optarg, "y")){
                                axis = Y;
                            }
                            else{
                                puts("In --reflect: incorrect values type or meaning (axis). It must be x or y");
                                exit(0);
                            }
                            break;
                        case 'v':
                            if(!strcmp(optarg, "right")){
                                vector = RIGHT;
                            }
                            else if(!strcmp(optarg, "left")){
                                vector = LEFT;
                            }
                            else if(!strcmp(optarg, "up")){
                                vector = UP;
                            }
                            else if(!strcmp(optarg, "down")){
                                vector = DOWN;
                            }
                            else{
                                puts("In --reflect: incorrect values type or meaning (vector). It must be up/down/left/right, also depending on the axis value");
                                exit(0);
                            }
                            break;
                        case 'f':
                            p2 = read_coordinates("--reflect");
                            break;
                        case 's':
                            p4 = read_coordinates("--reflect");
                            break;
                        case '?': puts("--reflect: wrong flags used or not enough variables"); exit(0);
                    }
                }
                if(axis == X && !(vector == DOWN || vector == UP)){
                    puts("For axis X you can use only UP (up) and DOWN (down) vectors");
                    exit(0);
                }
                if(axis == Y && !(vector == LEFT || vector == RIGHT)){
                    puts("For axis Y you can use only RIGHT (right) and LEFT (left) vectors");
                    exit(0);
                }
                Image = reflect(Image, axis, vector, p2, p4);
                break;
            case 'P':
                for(int var_count = 1; var_count <= 3; var_count++){
                    if((input = getopt_long(argc, argv, var_opts, a, NULL)) == -1){
                        puts("Not enough variables");
                        exit(0);
                    }
                    switch(input){
                        case 'f':
                            p2 = read_coordinates("--copy-and-paste");
                            break;
                        case 's':
                            p4 = read_coordinates("--copy-and-paste");
                            break;
                        case 'n':
                            newp2 = read_coordinates("--copy-and-paste");
                            break;
                        case '?': puts("--copy-and-paste: wrong flags used or not enough variables"); exit(0);
                    }
                }
                copy_and_paste(&Image, p2, p4, newp2);
                break;
            case 'Q':
                for(int var_count = 1; var_count <= 2; var_count++){
                    if((input = getopt_long(argc, argv, var_opts, a, NULL)) == -1){
                        puts("Not enough variables");
                        exit(0);
                    }
                    switch(input){
                        case 'f':
                            p2 = read_coordinates("--crop");
                            break;
                        case 's':
                            p4 = read_coordinates("--crop");
                            break;
                        case '?': puts("--crop: wrong flags used or not enough variables"); exit(0);
                    }
                }
                Image = area_copy(Image, p2, p4);
                break;
            case 'C':
                for(int var_count = 1; var_count <= 2; var_count++){
                    if((input = getopt_long(argc, argv, var_opts, a, NULL)) == -1){
                        puts("Not enough variables");
                        exit(0);
                    }
                    switch(input){
                        case 'd':
                            old = read_color("--color-change");
                            break;
                        case 'c':
                            newc = read_color("--color-change");
                            break;
                        case '?': puts("--color-change: wrong flags used or not enough variables"); exit(0);

                    }
                }
                color_change(&Image, old, newc);
                break;
            case 'N':
                if((input = getopt_long(argc, argv, var_opts, a, NULL)) == -1){
                    puts("Not enough variables");
                    exit(0);
                }
                color = read_color("--color-count");
                printf("Number of pixels with entered color: %d\n", color_count(Image, color));
                break;
            case 'G':
                for(int var_count = 1; var_count <= 3; var_count++){
                    if((input = getopt_long(argc, argv, var_opts, a, NULL)) == -1){
                        puts("Not enough variables");
                        exit(0);
                    }
                    switch(input){
                        case 'o':
                            path = malloc(sizeof(char)*strlen(optarg));
                            path = strcpy(path, optarg);
                            break;
                        case 'x':
                            if(isNum(optarg) && atoi(optarg) > 0){
                                x_parts = atoi(optarg);
                            }
                            else{
                                puts("In --clustering: incorrect value type or meaning (x_parts). It must be an integer and be greater than 0");
                                exit(0);
                            }
                            break;
                        case 'y':
                            if(isNum(optarg) && atoi(optarg) > 0){
                                y_parts = atoi(optarg);
                            }
                            else{
                                puts("In --clustering: incorrect value type or meaning (y_parts). It must be an integer and be greater than 0");
                                exit(0);
                            }
                            break;
                        case '?': puts("--clustering: wrong flags used or not enough variables"); exit(0);
                    }
                }
                clustering(Image, path, x_parts, y_parts);
                free(path);
                break;
            case 'T':
                for(int var_count = 1; var_count <= 4; var_count++){
                    if((input = getopt_long(argc, argv, var_opts, a, NULL)) == -1){
                        puts("Not enough variables");
                        exit(0);
                    }
                    switch(input){
                        case 'x':
                            if(isNum(optarg) && atoi(optarg) > 0){
                                x_parts = atoi(optarg);
                            }
                            else{
                                puts("In --separating: incorrect value type or meaning (x_parts). It must be an integer and be greater than 0");
                                exit(0);
                            }
                            break;
                        case 'y':
                            if(isNum(optarg) && atoi(optarg) > 0){
                                y_parts = atoi(optarg);
                            }
                            else{
                                puts("In --separating: incorrect value type or meaning (y_parts). It must be an integer and be greater than 0");
                                exit(0);
                            }
                            break;
                        case 't':
                            if(isNum(optarg) && atoi(optarg) > 0){
                                thickness = atoi(optarg);
                            }
                            else{
                                puts("In --separating: incorrect value type or meaning (thickness). It must be an integer and be greater than 0");
                                exit(0);
                            }
                            break;
                        case 'c':
                            color = read_color("--separating");
                            break;
                        case '?': puts("--separating: wrong flags used or not enough variables"); exit(0);
                    }
                }
                Image = separating(Image, x_parts, y_parts, thickness, color);
                break;
            case 'O':
                for(int var_count = 1; var_count <= 4; var_count++){
                    if((input = getopt_long(argc, argv, var_opts, a, NULL)) == -1){
                        puts("Not enough variables");
                        exit(0);
                    }
                    switch(input){
                        case 'r':
                            if(isNum(optarg) && atoi(optarg) > 0){
                                radius = atoi(optarg);
                            }
                            else{
                                puts("In --draw-circle: incorrect value type or meaning (radius). It must be an integer and be greater than 0");
                                exit(0);
                            }
                            break;
                        case 't':
                            if(isNum(optarg) && atoi(optarg) > 0){
                                thickness = atoi(optarg);
                            }
                            else{
                                puts("In --draw-circle: incorrect value type or meaning (thickness). It must be an integer and be greater than 0");
                                exit(0);
                            }
                            break;
                        case 'c':
                            color = read_color("--circle");
                            break;
                        case 'p':
                            p = read_coordinates("--circle");
                            break;
                        case '?': puts("--circle: wrong flags used or not enough variables"); exit(0);
                    }
                }
                Circle(&Image, radius, thickness, color, p);
                break;
            case 'L':
                for(int var_count = 1; var_count <= 2; var_count++){
                    if((input = getopt_long(argc, argv, var_opts, a, NULL)) == -1){
                        puts("Not enough variables");
                        exit(0);
                    }
                    switch(input){
                        case 'x':
                            if(isNum(optarg) && atoi(optarg) > 0){
                                x_parts = atoi(optarg);
                            }
                            else{
                                puts("In --collage: incorrect value type or meaning (x_parts). It must be an integer and be greater than 0");
                                exit(0);
                            }
                            break;
                        case 'y':
                            if(isNum(optarg) && atoi(optarg) > 0){
                                y_parts = atoi(optarg);
                            }
                            else{
                                puts("In --collage: incorrect value type or meaning (y_parts). It must be an integer and be greater than 0");
                                exit(0);
                            }
                            break;
                        case '?': puts("--collage: wrong flags used or not enough variables"); exit(0);
                    }
                }
                Image = collage(Image, x_parts, y_parts);
                break;
            case '?': puts("Wrong flag used for calling a function"); exit(0);
        }
        input = getopt_long(argc, argv, func_opts, a, NULL);
    }
    data_free(&Image);
    puts("Succesful!");
    return 0;
}