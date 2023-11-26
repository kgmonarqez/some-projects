#pragma once
#include "../../Player/Mechanics.h"

class Command{
public:
    virtual void action(Mechanics& Controller) = 0;
};