#ifndef TELEPORT_H
#define TELEPORT_H
#include "Event.h"
#include "../World/Point.h"

class Mechanics;

class Teleport: public Event{
private:
    Point Destination;
public:
    Teleport(Point Input_destinaton);
    bool action(Mechanics& Controller);
    Teleport* copy();
};
#endif