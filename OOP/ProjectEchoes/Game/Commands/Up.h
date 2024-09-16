#pragma once
#include "Command.h"

class Up: public Command{
private:
    char Key;
public:
    void action(Mechanics& Controller);
    Up(char Settings_key);
    char get_key();
};