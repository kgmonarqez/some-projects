#pragma once
#include "Command.h"

class Left: public Command{
private:
    char Key;
public:
    void action(Mechanics& Controller);
    Left(char Settings_key);
    char get_key();
};