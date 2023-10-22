#pragma once
#include "Event.h"

#define HEAL_POINTS 10

class Heal: public Event{
public:
    void action(Mechanics& Controller);
};