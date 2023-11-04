#pragma once
#include "Event.h"
#include "../World/Point.h"

class Point;

class Teleport: public Event{
private:
    Point Destination;
public:
    Teleport(Point Input_destinaton);
    bool action(Mechanics& Controller);
    Teleport* copy();
};