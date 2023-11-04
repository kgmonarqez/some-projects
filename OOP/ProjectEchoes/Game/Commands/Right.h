#pragma once
#include "Command.h"

class Right: public Command{
private:
    char Key;
public:
    void action(Mechanics& Controller);
    Right(char Settings_key);
    char get_key();
};