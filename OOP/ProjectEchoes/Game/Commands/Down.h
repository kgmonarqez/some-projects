#pragma once
#include "Command.h"

class Down: public Command{
private:
    char Key;
public:
    void action(Mechanics& Controller);
    Down(char Settings_key);
    char get_key();
};