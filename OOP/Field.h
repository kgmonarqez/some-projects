#pragma once
#include "Cell.h"
#include "Point.h"

#define DEFAULT_FIELD_SIZE_X 10
#define DEFAULT_FIELD_SIZE_Y 10
#define MIN_FIELD_SIZE_X 5
#define MIN_FIELD_SIZE_Y 5

class Field{
private:    
    class Cell ***Map;
    int Field_size_x;
    int Field_size_y;
    
    Point Entrance;   
    Point Exit;

public:
    Field(int Input_field_size_x=DEFAULT_FIELD_SIZE_X, int Input_field_size_y=DEFAULT_FIELD_SIZE_Y);
    ~Field();

    int get_field_size_x();
    int get_field_size_y();

    bool check_passing(int x, int y);
};