#include "DataBaseIO.h"

char* readString(FILE* f){
    if(f){
        int bufSize = STRING_SIZE;
        char q;
        int length = 0;
        char* str = malloc(sizeof(char) * bufSize);
        if(str){
            while((q = fgetc(f)) != '\n' && q != EOF){
                if(length > bufSize - 2){
                    bufSize += STRING_SIZE;
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

char* process(char* ptr){
    if(ptr){
        int n = strlen(ptr) - 1;
        if(ptr && n > 0){
            while(isspace(*ptr)){
                ptr++;
            }
            int n = strlen(ptr) - 1;
            while(n >= 0 && isspace(ptr[n])){
                n--;
            }
            n++;
            if(n > 0){
                char* str = malloc(sizeof(char) * n);
                if(!str){
                    perror("Dynamic memory err");
                    exit(1);
                }
                strcpy(str, ptr);
                str[n] = '\0';
                return str;
            }
        }
    }
    return "None";
}

Movie buildMovieStruct(char* movieString, int pos){
    Movie currentMovie = {NULL, NULL, NULL, NULL, NULL, pos};

    char* ptr = strtok(movieString, "/");
    currentMovie.director = process(ptr);
            
    ptr = strtok(NULL, "/");
    currentMovie.name = process(ptr);
        
    ptr = strtok(NULL, "/");
    currentMovie.year = process(ptr);

    ptr = strtok(NULL, "/");
    currentMovie.copiesCount = process(ptr);
        
    ptr = strtok(NULL, "/");
    currentMovie.cost = process(ptr);
    return currentMovie;
}

MoviesDataBase readDB(char* fileName){
    FILE* f = fopen(fileName, "r");
    if(!f || !fileName){
        puts("File with this name doesn't exist");
        return (MoviesDataBase){NULL, 0};
    }
    
    int n = 0;
    int bufSize = DB_SIZE;
    Movie* movieList = malloc(sizeof(Movie) * bufSize);
    if(movieList){
        while(!feof(f)){
            char* movieString = caesarDecoder(readString(f));
            if(movieString && strlen(movieString)){
                if(n == bufSize){
                    bufSize += DB_SIZE;
                    Movie* tmp = realloc(movieList, sizeof(Movie) * bufSize);
                    movieList = tmp;
                }
                if(movieList){
                    movieList[n++] = buildMovieStruct(movieString, n);
                    free(movieString);
                }
                else{
                    perror("Dynamic memory err");
                    exit(1);
                }
            }
        }
    }
    else{
        perror("Dynamic memory err");
        exit(1);
    }
    if(movieList){
        puts("Data base opened");
    }
    fclose(f);
    return (MoviesDataBase){movieList, n};
}

void printTitle(){
    for(int i = 0; i < 97; i++){
        printf("=");
    }
    puts("");
    printf("|%-5s|%-25s|%-25s|%-10s|%-15s|%-10s|\n", "#", STR_DIRECTOR, STR_NAME, STR_YEAR, STR_COPIES, STR_COST);
    for(int i = 0; i < 97; i++){
        printf("=");
    }
    puts("");
}

void printMovie(Movie M){
    printf("|%-5d|%-25s|%-25s|%-10s|%-15s|%-10s|\n", M.pos, M.director, M.name, M.year, M.copiesCount, M.cost);
}

void printDB(MoviesDataBase MDB){
    printTitle();
    for(int i = 0; i < MDB.n; i++){
        Movie M = MDB.movieList[i];
        printMovie(M);
    }
    for(int i = 0; i < 97; i++){
        printf("=");
    }
    puts("");
}

void saveDB(MoviesDataBase MDB, char* fileName){
    FILE* f = fopen(fileName, "w");
    char* outputStr = NULL;
    Movie* mList = MDB.movieList;
    if(f){
        for(int i = 0; i < MDB.n; i++){
            outputStr = malloc(sizeof(char) * 
                (strlen(mList[i].director) + strlen(mList[i].name) + strlen(mList[i].year) + strlen(mList[i].copiesCount) + strlen(mList[i].cost)) + 3*4 + 1);
            if(outputStr){
                sprintf(outputStr, "%s / %s / %s / %s / %s\n", mList[i].director, mList[i].name, mList[i].year, mList[i].copiesCount, mList[i].cost);
                outputStr = caesarEncoder(outputStr);
                fwrite(outputStr, sizeof(char), strlen(outputStr), f);
                free(outputStr);
            }
            else{
                perror("Dynamic memory err");
                exit(1);
            }
        }
        fclose(f);
    }
    else{
        puts("File with this name doesn't exist");
    }
}

char* caesarDecoder(char* str){
    for(int i = 0; i < strlen(str); i++){
        if(str[i] != '\n'){
            str[i] += STEP;
        }
    }
    return str;
}

char* caesarEncoder(char* str){
    for(int i = 0; i < strlen(str); i++){
        if(str[i] != '\n'){
            str[i] -= STEP;
        }
    }
    return str;
}

/*
Mary Harron / American Psycho / 2000 / 200000 / 150
Mary Harron / American Psycho / 2000 / 200000 / 150
Mary Harron / American Psycho / 2000 / 200000 / 150
David Fincher / Fight Club / 1999 / 1000000 / 50
Mary Harron / American Psycho / 2000 / 200000 / 150
Who Knows / Green Elephant / 2002 / 9092 / 1000
*/