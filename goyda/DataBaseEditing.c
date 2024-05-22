#include "DataBaseEditing.h"

int isEdited = 0;

void editMovie(MoviesDataBase* MDB, int n, dataTypes dataType, char* newData){
    if(n < MDB->n && MDB->movieList && newData && n >= 0){
        switch(dataType){
            case DIRECTOR:
                if(MDB->movieList[n].director){
                    free(MDB->movieList[n].director);
                }
                MDB->movieList[n].director = malloc(sizeof(char) * strlen(newData));
                if(MDB->movieList[n].director){
                    strcpy(MDB->movieList[n].director, newData);
                }
                else{
                    perror("Dynamic memory err");
                    exit(1);
                }
                break;
            case NAME:
                if(MDB->movieList[n].name){
                    free(MDB->movieList[n].name);
                }
                MDB->movieList[n].name = malloc(sizeof(char) * strlen(newData));
                if(MDB->movieList[n].name){
                    strcpy(MDB->movieList[n].name, newData);
                }
                else{
                    perror("Dynamic memory err");
                    exit(1);
                }
                break;
            case YEAR:
                if(checkIsNum(newData)){
                    if(MDB->movieList[n].year){
                        free(MDB->movieList[n].year);
                    }
                    MDB->movieList[n].year = malloc(sizeof(char) * strlen(newData));
                    if(MDB->movieList[n].year){
                        strcpy(MDB->movieList[n].year, newData);
                    }
                    else{
                        perror("Dynamic memory err");
                        exit(1);
                    }
                }
                else{
                    puts("Year parameter must be an integer");
                    return;
                }
                break;
            case COPIES:
                if(checkIsNum(newData)){
                    if(MDB->movieList[n].copiesCount){
                        free(MDB->movieList[n].copiesCount);
                    }
                    MDB->movieList[n].copiesCount = malloc(sizeof(char) * strlen(newData));
                    if(MDB->movieList[n].copiesCount){
                        strcpy(MDB->movieList[n].copiesCount, newData);
                    }
                    else{
                        perror("Dynamic memory err");
                        exit(1);
                    }
                }
                else{
                    puts("Copies parameter must be an integer");
                    return;
                }
                break;
            case COST:
                if(checkIsNum(newData)){
                    if(MDB->movieList[n].cost){
                        free(MDB->movieList[n].cost);
                    }
                    MDB->movieList[n].cost = malloc(sizeof(char) * strlen(newData));
                    if(MDB->movieList[n].cost){
                        strcpy(MDB->movieList[n].cost, newData);
                    }
                    else{
                        perror("Dynamic memory err");
                        exit(1);
                    }
                }
                else{
                    puts("Cost parameter must be an integer");
                    return;
                }
                break;
            case NONE:
                puts("Current data type doesn't exist");
                return;
        }
        printf("Movie №%d edited\n", n+1);
        isEdited = 1;
    }
    else{
        puts("Not enough agruments");
    }
}

void addMovie(MoviesDataBase* MDB, char* info){
    if(!MDB->movieList){
        MDB->movieList = malloc(sizeof(Movie) * DB_SIZE);
    }
    if(MDB->n % DB_SIZE == 0){
        Movie* tmp = realloc(MDB->movieList, (MDB->n + DB_SIZE) * sizeof(Movie));
        MDB->movieList = tmp;
    }
    if(MDB->movieList){
        MDB->movieList[MDB->n++] = buildMovieStruct(info, MDB->n+1);  
        isEdited = 1;
    }
}

void popMovie(MoviesDataBase* MDB, int n){
    if(n < MDB->n && n >= 0 && MDB->movieList){
        Movie* ptr = MDB->movieList;
        memmove(ptr + n, ptr + n + 1, (MDB->n - n - 1) * sizeof(Movie));
        MDB->n--;
        Movie* tmp = realloc(ptr, MDB->n*sizeof(Movie));
        MDB->movieList = tmp;
        if(!MDB->movieList && MDB->n){
            perror("Dynamic memory err");
            exit(1);
        }
        for(int i = n; i < MDB->n; i++){
            MDB->movieList[i].pos--;
        }
        isEdited = 1;
    }
}

void sortList(MoviesDataBase* MDB, dataTypes dataType, sortingOrder order){
    int (*func)(const void*, const void*);
    switch(dataType){
        case DIRECTOR:
            if(order == ASCENDING){
                func = directorComparator;
            }
            else if(order == DESCENDING){
                func = directorComparatorDescending;
            }
            break;
        case NAME:
            if(order == ASCENDING){
                func = nameComparator;
            }
            else if(order == DESCENDING){
                func = nameComparatorDescending;
            }
            break;
        case YEAR:
            if(order == ASCENDING){
                func = yearComparator;
            }
            else if(order == DESCENDING){
                func = yearComparatorDescending;
            }
            break;
        case COPIES:
            if(order == ASCENDING){
                func = copiesCountComparator;
            }
            else if(order == DESCENDING){
                func = copiesCountComparatorDescending;
            }
            break;
        case COST:
            if(order == ASCENDING){
                func = costComparator;
            }
            else if(order == DESCENDING){
                func = costComparatorDescending;
            }
            break;
        default:
            func = NULL;
            break;
    }
    if(func){
        qsort(MDB->movieList, MDB->n, sizeof(Movie), func);
        for(int i = 0; i < MDB->n; i++){
            MDB->movieList[i].pos = i+1;
        }
        isEdited = 1;
    }
    else{
        puts("Sorting: wrong data type");
    }
}

void searchMovies(MoviesDataBase* MDB, dataTypes dataType, char* searchingData){
    if(searchingData){
        Movie M = {NULL, NULL, NULL, NULL, NULL, -1};
        int(*comparator)(const void*, const void*);   // Указатель на функцию
        switch(dataType){
            case DIRECTOR:
                comparator = directorComparator;
                M.director = searchingData;
                break;
            case NAME:
                comparator = nameComparator;
                M.name = searchingData;
                break;
            case YEAR:
                comparator = yearComparator;
                M.year = searchingData;
                break;
            case COPIES:
                comparator = copiesCountComparator;
                M.copiesCount = searchingData;
                break;
            case COST:
                comparator = costComparator;
                M.cost = searchingData;
                break;
            case NONE:
                puts("Wrong data type");
                comparator = NULL;
                return;
        }

        int k = 0;
        if(comparator){
            printTitle();
            for(int i = 0; i < MDB->n; i++){
                if(!comparator(&MDB->movieList[i], &M)){
                    printMovie(MDB->movieList[i]);
                }
            }
            puts("");
        }
    }
    else{
        puts("No searchable data");
    }
}

int directorComparator(const void* M1, const void* M2){
    char* str1 = ((Movie*)M1)->director;
    char* str2 = ((Movie*)M2)->director;
    return strcmp(str1, str2);
}

int directorComparatorDescending(const void* M1, const void* M2){
    char* str1 = ((Movie*)M1)->director;
    char* str2 = ((Movie*)M2)->director;
    return strcmp(str2, str1);
}

int nameComparator(const void* M1, const void* M2){
    char* str1 = ((Movie*)M1)->name;
    char* str2 = ((Movie*)M2)->name;
    return strcmp(str1, str2);
}

int nameComparatorDescending(const void* M1, const void* M2){
    char* str1 = ((Movie*)M1)->name;
    char* str2 = ((Movie*)M2)->name;
    return strcmp(str2, str1);
}

int yearComparator(const void* M1, const void* M2){
    int num1 = atoi(((Movie*)M1)->year);
    int num2 = atoi(((Movie*)M2)->year);
    return num1 - num2;
}

int yearComparatorDescending(const void* M1, const void* M2){
    int num1 = atoi(((Movie*)M1)->year);
    int num2 = atoi(((Movie*)M2)->year);
    return num2 - num1;
}

int copiesCountComparator(const void* M1, const void* M2){
    int num1 = atoi(((Movie*)M1)->copiesCount);
    int num2 = atoi(((Movie*)M2)->copiesCount);
    return num1 - num2;
}

int copiesCountComparatorDescending(const void* M1, const void* M2){
    int num1 = atoi(((Movie*)M1)->copiesCount);
    int num2 = atoi(((Movie*)M2)->copiesCount);
    return num2 - num1;
}

int costComparator(const void* M1, const void* M2){
    int num1 = atoi(((Movie*)M1)->cost);
    int num2 = atoi(((Movie*)M2)->cost);
    return num1 - num2;
}

int costComparatorDescending(const void* M1, const void* M2){
    int num1 = atoi(((Movie*)M1)->cost);
    int num2 = atoi(((Movie*)M2)->cost);
    return num2 - num1;
}

int getMaxValue(MoviesDataBase MDB, int (*comparator)(const void*, const void*), dataTypes dt){
    int res = 0;
    if(MDB.movieList && comparator){
        Movie max = MDB.movieList[0];
        for(int i = 1; i < MDB.n; i++){
            if(comparator(&max, &MDB.movieList[i]) < 0){
                max = MDB.movieList[i];
            }
        }
        
        switch(dt){
            case YEAR:
                res = atoi(max.year);
                break;
            case COPIES:
                res = atoi(max.copiesCount);
                break;
            case COST:
                res = atoi(max.cost);
                break;
        }
    }
    return res;
}

int getMinValue(MoviesDataBase MDB, int (*comparator)(const void*, const void*), dataTypes dt){
    int res = 0;
    if(MDB.movieList && comparator){
        Movie min = MDB.movieList[0];
        for(int i = 1; i < MDB.n; i++){
            if(comparator(&min, &MDB.movieList[i]) > 0){
                min = MDB.movieList[i];
            }
        }
        
        switch(dt){
            case YEAR:
                res = atoi(min.year);
                break;
            case COPIES:
                res = atoi(min.copiesCount);
                break;
            case COST:
                res = atoi(min.cost);
                break;
        }
    }
        return res;
}

double getMidValue(MoviesDataBase MDB, int (*comparator)(const void*, const void*), dataTypes dt){
    if(MDB.movieList && comparator){
        double res = 0;
        for(int i = 0; i < MDB.n; i++){
            switch(dt){
                case YEAR:
                    res += atoi(MDB.movieList[i].year);
                    break;
                case COPIES:
                    res += atoi(MDB.movieList[i].copiesCount);
                    break;
                case COST:
                    res += atoi(MDB.movieList[i].cost);
                    break;
            }
        }
        return res / MDB.n;
    }
    return 0;
}

void showStatistics(MoviesDataBase MDB, dataTypes dt){
    int (*comparator)(const void*, const void*) = NULL;
    char* dataName = NULL;
    switch(dt){
        case YEAR:
            comparator = yearComparator;
            dataName = STR_YEAR;
            break;
        case COPIES:
            comparator = copiesCountComparator;
            dataName = STR_COPIES;
            break;
        case COST:
            comparator = costComparator;
            dataName = STR_COST;
            break;
        default:
            puts("Unidentified data category or this category is not integer");
            return;
    }

    printf("Maximum %s: %d\n", dataName, getMaxValue(MDB, comparator, dt));
    printf("Minimum %s: %d\n", dataName, getMinValue(MDB, comparator, dt));
    printf("Medium %s: %f\n", dataName, getMidValue(MDB, comparator, dt));
}