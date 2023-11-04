#pragma once
#include "../../Player/Mechanics.h"

class Command{
public:
    virtual void action(Mechanics& Controller) = 0;
    virtual char get_key() = 0;
};