#pragma once
#include "Event.h"

class Finish: public Event{
    bool action(Mechanics& Controller);
    Finish* copy();
    char get_representation();
};