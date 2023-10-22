#pragma once
#include <algorithm>
#include "Cell.h"
#include "Point.h"

#define DEFAULT_FIELD_SIZE_X 10
#define DEFAULT_FIELD_SIZE_Y 10
#define MIN_FIELD_SIZE_X 5
#define MIN_FIELD_SIZE_Y 5

class Cell;
class Point;

class Field{
private:    
    class Cell** Map;
    int Field_size_x;
    int Field_size_y;
    
    Point Start;   
    Point Destination;
public:
    Field(int Input_field_size_x=DEFAULT_FIELD_SIZE_X, int Input_field_size_y=DEFAULT_FIELD_SIZE_Y);
    Field(const Field& Copy);
    Field(Field&& Move);
    ~Field();

    Field& operator=(const Field& Copy);
    Field& operator=(Field&& Move);

    int get_field_size_x();
    int get_field_size_y();

    Cell& get_cell(int x, int y);
    Point get_start();

    bool check_passing(int x, int y);

    void set_start(Point New_start);
    void set_destination(Point New_destination);
};