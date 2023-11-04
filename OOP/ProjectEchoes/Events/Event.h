#pragma once
#include "../Player/Mechanics.h"
#include "../Player/Player.h"

class Mechanics;
class Player;

class Event{
public:
    virtual bool action(Mechanics& Controller) = 0;
    virtual Event* copy() = 0;
};