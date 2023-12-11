#include "Point.h"

Point::Point(int Input_x, int Input_y){
    set_x(Input_x);
    set_y(Input_y);
}

Point::Point(){}

int Point::get_x(){
    return x;
}

int Point::get_y(){
    return y;
}

void Point::set_x(int Input_x){
    x = Input_x;
}

void Point::set_y(int Input_y){
    y = Input_y;
}

bool Point::operator==(const Point& P){
    return x == P.x && y == P.y;
}