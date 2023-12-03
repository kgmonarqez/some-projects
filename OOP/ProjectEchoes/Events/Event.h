#ifndef EVENT_H
#define EVENT_H
#include "../Player/Mechanics.h"

class Mechanics;

class Event{
public:
    virtual bool action(Mechanics& Controller) = 0;
    virtual Event* copy() = 0;
};
#endif