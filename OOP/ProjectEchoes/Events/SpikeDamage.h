#pragma once
#include "Event.h"

#define SPIKE_DAMAGE 10

class SpikeDamage: public Event{
public:
    bool action(Mechanics& Controller);
    SpikeDamage* copy();
};