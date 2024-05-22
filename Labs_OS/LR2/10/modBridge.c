#include <stdio.h>

int main(int argc, char* argv[]){
    char* fileName = argv[1];
    FILE* fptr;
    fptr = fopen(fileName, "r");
    if(!fptr){
        printf("Couldn't find or open file\n");
        return 1;
    }

    char string[255];
    while(fgets(string, 255, fptr)){
        printf("%s", string);
    }
    return 0;
}