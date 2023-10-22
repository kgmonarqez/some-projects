#pragma once
#include "Event.h"

class Finish: public Event{
    void action(Mechanics& Controller);
};