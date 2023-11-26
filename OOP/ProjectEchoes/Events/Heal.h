#ifndef HEAL_H
#define HEAL_H
#include "Event.h"

#define HEAL_POINTS 10

class Mechanics;

class Heal: public Event{
public:
    bool action(Mechanics& Controller);
    Heal* copy();
    char get_representation();
};
#endif