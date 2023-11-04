#pragma once
#include "Point.h"

class Portal{
private:
    Point Entrance;
    Point Exit;
public:
    Portal(Point Input_entrance, Point Input_exit);
    Point get_entrance();
    Point get_exit();
    bool check_if_entrance(int x, int y){
        return x == Entrance.get_x() && y == Entrance.get_y();
    }
};