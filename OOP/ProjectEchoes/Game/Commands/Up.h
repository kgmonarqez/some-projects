#pragma once
#include "Command.h"

class Up: public Command{
public:
    void action(Mechanics& Controller);
};