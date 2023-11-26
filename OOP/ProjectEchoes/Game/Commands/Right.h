#pragma once
#include "Command.h"

class Right: public Command{
public:
    void action(Mechanics& Controller);
};