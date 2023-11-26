#ifndef SPIKE_H
#define SPIKE_H
#include "Event.h"

#define SPIKE_DAMAGE 10

class Mechanics;

class SpikeDamage: public Event{
public:
    bool action(Mechanics& Controller);
    SpikeDamage* copy();
    char get_representation();
};
#endif