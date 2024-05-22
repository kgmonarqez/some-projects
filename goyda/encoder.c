#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 10
#define STEP 10

char* caesarEncoder(char* str){
    for(int i = 0; i < strlen(str); i++){
        if(str[i] != '\n'){
            str[i] -= STEP;
        }
    }
    return str;
}

char* readString(FILE* f){
    if(f){
        int bufSize = STR_SIZE;
        char q;
        int length = 0;
        char* str = malloc(sizeof(char) * bufSize);
        if(str){
            while((q = fgetc(f)) != EOF){
                if(length > bufSize - 2){
                    bufSize += STR_SIZE;
                    char* tmp = realloc(str, sizeof(char) * bufSize);
                    str = tmp;
                }
                if(str){
                    str[length++] = q;
                }
                else{
                    perror("Dynamic memory err");
                    exit(1);
                }
            }    
            str[length] = '\0';
            return str;
        }
        else{
            perror("Dynamic memory err");
            exit(1);
        }
    }
    return NULL;
}

void encodeFile(char* fileName){
    FILE* f = fopen(fileName, "r");
    if(f){
        char* str = caesarEncoder(readString(f));
        fclose(f);
        fopen(fileName, "w");
        if(f){
            fwrite(str, sizeof(char), strlen(str), f);
        }
    }
}

int main(int argc, char** argv){
    if(argc > 1){
        encodeFile(argv[1]);
    }
    else{
        puts("No file name");
    }
    return 0;
}