#pragma once

class Point{
private:
    int x;
    int y;
public:
    Point(int Input_x, int Input_y);

    Point();

    int get_x();
    int get_y();

    void set_x(int Input_x);
    void set_y(int Input_y);

    bool operator==(const Point& P);
};