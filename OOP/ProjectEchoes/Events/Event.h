#pragma once
#include "../Player/Mechanics.h"
#include "../Player/Player.h"

class Mechanics;
class Player;

class Event{
public:
    virtual void action(Mechanics& Controller) = 0;
};