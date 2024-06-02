#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DB_SIZE 5
#define STRING_SIZE 5
#define DB_DELIM '/'
#define DB_ELEMENT_SIZE 5

#define STR_EXIT "quit"
#define STR_OPEN "open"
#define STR_SAVE "save"
#define STR_SHOW "show"
#define STR_EDIT "edit"
#define STR_ADD "add"
#define STR_POP "remove"
#define STR_SORT "sort"
#define STR_SEARCH "find"
#define STR_HELP "help"
#define STR_STAT "stat"

#define STR_DIRECTOR "Director"
#define STR_NAME "Name"
#define STR_YEAR "Year"
#define STR_COPIES "Copies"
#define STR_COST "Cost"

#define STR_ASCENDING "+"
#define STR_DESCENDING "-"

typedef enum dataTypes {NONE, DIRECTOR, NAME, YEAR, COPIES, COST} dataTypes;
typedef enum sortingOrder {ASCENDING, DESCENDING} sortingOrder;
typedef enum operation {CMD_NONE, CMD_EXIT, CMD_OPEN, CMD_SAVE, CMD_SHOW, 
                        CMD_EDIT, CMD_ADD, CMD_POP, CMD_SORT, CMD_SEARCH, CMD_HELP, CMD_STAT} operation;

typedef struct Movie{
    char director[STRING_SIZE + 1];
    char name[STRING_SIZE + 1];
    char year[STRING_SIZE + 1];
    char copiesCount[STRING_SIZE + 1];
    char cost[STRING_SIZE + 1];
    int pos;
} Movie;

typedef struct MoviesDataBase{
    Movie* movieList;
    int n;
} MoviesDataBase;

char* readSTDIN(char* message);
operation menu(char* command);
dataTypes defineDataType(char* dt);
sortingOrder defineSortingOrder(char* so);
int checkIsNum(char* str);
int extractNum(char* data);
void printHelp();
int askForSaving();