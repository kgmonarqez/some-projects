#include "DataBaseEditing.h"

int isEdited = 0;

void editMovie(MoviesDataBase* MDB, int n, dataTypes dataType, char* newData){
    if(n < MDB->n && MDB->movieList && newData && n >= 0){
        int length = STRING_SIZE+1;
        if(strlen(newData)+1 < length){
            length = strlen(newData)+1;
        }
        switch(dataType){
            case DIRECTOR:
                memmove(MDB->movieList[n].director, newData, length);
                if(length == STRING_SIZE+1){
                    MDB->movieList[n].director[STRING_SIZE] = '\0';
                }
                break;
            case NAME:
                memmove(MDB->movieList[n].name, newData, length);
                if(length == STRING_SIZE+1){
                    MDB->movieList[n].name[STRING_SIZE] = '\0';
                }
                break;
            case YEAR:
                memmove(MDB->movieList[n].year, newData, length);
                if(length == STRING_SIZE+1){
                    MDB->movieList[n].year[STRING_SIZE] = '\0';
                }
                break;
            case COPIES:
                memmove(MDB->movieList[n].copiesCount, newData, length);
                if(length == STRING_SIZE+1){
                    MDB->movieList[n].copiesCount[STRING_SIZE] = '\0';
                }
                break;
            case COST:
                memmove(MDB->movieList[n].cost, newData, length);
                if(length == STRING_SIZE+1){
                    MDB->movieList[n].cost[STRING_SIZE] = '\0';
                }
                break;
            case NONE:
                puts("Current data type doesn't exist");
                return;
        }
        printf("Movie №%d edited\n", n+1);
        isEdited = 1;
    }
}

void addMovie(MoviesDataBase* MDB, Movie newMovie){
    if(!MDB->movieList){
        MDB->movieList = malloc(sizeof(Movie) * DB_SIZE);
    }
    if(MDB->n % DB_SIZE == 0){
        Movie* tmp = realloc(MDB->movieList, (MDB->n + DB_SIZE) * sizeof(Movie));
        MDB->movieList = tmp;
    }
    if(MDB->movieList){
        newMovie.pos = MDB->n+1;
        MDB->movieList[MDB->n++] = newMovie;  
        isEdited = 1;
    }
}

Movie initMovie(){
    Movie newMovie;

    int length = STRING_SIZE+1;
    char* buf = readSTDIN("Director: ");
    while(!strlen(buf)){
        puts("Please type director data");
        free(buf);
        buf = readSTDIN("Director: ");
    }
    if(strlen(buf)+1 < length){
        length = strlen(buf)+1;
    }
    else{
        buf[STRING_SIZE] = '\0';
    }
    memmove(newMovie.director, buf, length);
    free(buf);

    length = STRING_SIZE+1;
    buf = readSTDIN("Name: ");
    while(!strlen(buf)){
        puts("Please type name data");
        free(buf);
        buf = readSTDIN("Name: ");
    }
    if(strlen(buf)+1 < length){
        length = strlen(buf)+1;
    }
    else{
        buf[STRING_SIZE] = '\0';
    }
    memmove(newMovie.name, buf, length);
    free(buf);

    length = STRING_SIZE+1;
    buf = readSTDIN("Year: ");
    while(!strlen(buf) || !checkIsNum(buf)){
        if(!strlen(newMovie.year)){
            puts("Please type year data");
        }
        else if(!checkIsNum(newMovie.year)){
            puts("Year data must be an integer");
        }
        free(buf);
        buf = readSTDIN("Year: ");
    }
    if(strlen(buf)+1 < length){
        length = strlen(buf)+1;
    }
    else{
        buf[STRING_SIZE] = '\0';
    }
    memmove(newMovie.year, buf, length);
    free(buf);

    length = STRING_SIZE+1;
    buf = readSTDIN("Copies: ");
    while(!strlen(buf) || !checkIsNum(buf)){
        if(!strlen(newMovie.copiesCount)){
            puts("Please type copies data");
        }
        else if(!checkIsNum(newMovie.copiesCount)){
            puts("Copies data must be an integer");
        }
        free(buf);
        buf = readSTDIN("Copies: ");
    }
    if(strlen(buf)+1 < length){
        length = strlen(buf)+1;
    }
    else{
        buf[STRING_SIZE] = '\0';
    }
    memmove(newMovie.copiesCount, buf, length);
    free(buf);

    length = STRING_SIZE+1;
    buf = readSTDIN("Cost: ");
    while(!strlen(buf) || !checkIsNum(buf)){
        if(!strlen(newMovie.cost)){
            puts("Please type cost data");
        }
        else if(!checkIsNum(newMovie.cost)){
            puts("Cost data must be an integer");
        }
        free(buf);
        buf = readSTDIN("Cost: ");
    }
    if(strlen(buf)+1 < length){
        length = strlen(buf)+1;
    }
    else{
        buf[STRING_SIZE] = '\0';
    }
    memmove(newMovie.cost, buf, length);
    free(buf);
    
    return newMovie;
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
        Movie M;
        int length = STRING_SIZE+1;
        if(strlen(searchingData)+1 < length){
            length = strlen(searchingData)+1;
        }
        int(*comparator)(const void*, const void*);   // Указатель на функцию
        switch(dataType){
            case DIRECTOR:
                comparator = directorComparator;
                memmove(M.director, searchingData, STRING_SIZE+1);
                if(length == STRING_SIZE+1){
                    M.director[STRING_SIZE] = '\0';
                }
                break;
            case NAME:
                comparator = nameComparator;
                memmove(M.name, searchingData, STRING_SIZE+1);
                if(length == STRING_SIZE+1){
                    M.name[STRING_SIZE] = '\0';
                }
                break;
            case YEAR:
                comparator = yearComparator;
                memmove(M.year, searchingData, STRING_SIZE+1);
                if(length == STRING_SIZE+1){
                    M.year[STRING_SIZE] = '\0';
                }
                break;
            case COPIES:
                comparator = copiesCountComparator;
                memmove(M.copiesCount, searchingData, STRING_SIZE+1);
                if(length == STRING_SIZE+1){
                    M.copiesCount[STRING_SIZE] = '\0';
                }
                break;
            case COST:
                comparator = costComparator;
                memmove(M.cost, searchingData, STRING_SIZE+1);
                if(length == STRING_SIZE+1){
                    M.cost[STRING_SIZE] = '\0';
                }
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
            for(int i = 0; i < 97; i++){
                printf("=");
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