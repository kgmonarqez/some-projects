#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>

#include "cmd.h"

#define STEP 10

MoviesDataBase readDB(char* fileName);
Movie buildMovieStruct(char* movieString, int pos);
char* readString(FILE* f);
void printTitle();
void printMovie(Movie M);
void printDB(MoviesDataBase MDB);
char* process(char* ptr);
void saveDB(MoviesDataBase MDB, char* fileName);
char* caesarDecoder(char* str);
char* caesarEncoder(char* str);
char* recoverFromStrtok(char* str, int n);