#pragma once
#include "Event.h"
#include "../World/Point.h"

class Point;

class Teleport: public Event{
private:
    Point Destination;
public:
    Teleport(Point Input_destinaton);
    void action(Mechanics& Controller);
};