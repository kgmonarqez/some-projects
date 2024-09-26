#pragma once
#include "Command.h"

class Down: public Command{
public:
    void action(Mechanics& Controller);
};