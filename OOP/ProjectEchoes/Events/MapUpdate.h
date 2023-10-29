#pragma once
#include "Event.h"

class MapUpdate: public Event{
public:
    bool action(Mechanics& Controller);
};