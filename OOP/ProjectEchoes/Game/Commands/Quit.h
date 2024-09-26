#pragma once
#include "Command.h"

class Quit: public Command{
    void action(Mechanics& Controller);
};