#pragma once
#include <stdlib.h>

#include "cmd.h"
#include "DataBaseIO.h"

extern int isEdited;

void editMovie(MoviesDataBase* MDB, int n, dataTypes dataType, char* newData);
void addMovie(MoviesDataBase* MDB, Movie newMovie);
Movie initMovie();
void popMovie(MoviesDataBase* MDB, int n);
void sortList(MoviesDataBase* MDB, dataTypes dataType, sortingOrder order);
void searchMovies(MoviesDataBase* MDB, dataTypes dataType, char* searchingData);

int directorComparator(const void* M1, const void* M2);
int directorComparatorDescending(const void* M1, const void* M2);

int nameComparator(const void* M1, const void* M2);
int nameComparatorDescending(const void* M1, const void* M2);

int yearComparator(const void* M1, const void* M2);
int yearComparatorDescending(const void* M1, const void* M2);

int copiesCountComparator(const void* M1, const void* M2);
int copiesCountComparatorDescending(const void* M1, const void* M2);

int costComparator(const void* M1, const void* M2);
int costComparatorDescending(const void* M1, const void* M2);

void showStatistics(MoviesDataBase MDB, dataTypes dt);
int getMaxValue(MoviesDataBase MDB, int (*comparator)(const void*, const void*), dataTypes dt); // Считать макс значение по одной из числовых характеристик
int getMinValue(MoviesDataBase MDB, int (*comparator)(const void*, const void*), dataTypes dt);
double getMidValue(MoviesDataBase MDB, int (*comparator)(const void*, const void*), dataTypes dt); // Среднее значение из всех числовых характеристик

