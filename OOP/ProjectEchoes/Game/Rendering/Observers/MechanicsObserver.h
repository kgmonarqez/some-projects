#pragma once
#include "../../../Player/Mechanics.h"

class Mechanics;

class MechanicsObserver{
public:
    virtual void update() = 0;
};