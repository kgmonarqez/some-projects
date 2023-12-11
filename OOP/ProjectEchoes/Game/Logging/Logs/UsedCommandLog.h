#pragma once
#include "Log.h"
#include "../../Commands/Command.h"
#include "../../Input/Input.h"

class UsedCommandLog: public Log{
private:
    Input*& ObservedInputSystem;

    std::pair<unsigned int, Command*> Used_command;
public:
    UsedCommandLog(Input*& InputSystem);
    std::pair<unsigned int, Command*> get_command() const;
    void update();
};