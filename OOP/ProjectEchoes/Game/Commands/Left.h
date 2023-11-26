#pragma once
#include "Command.h"

class Left: public Command{
public:
    void action(Mechanics& Controller);
};