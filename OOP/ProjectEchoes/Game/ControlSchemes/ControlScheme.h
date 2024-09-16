#pragma once
#include <map>
#include <iostream>
#include <termios.h>

#include "../Commands/Command.h"
#include "../Commands/Left.h"
#include "../Commands/Right.h"
#include "../Commands/Up.h"
#include "../Commands/Down.h"

enum class CommandNames{LEFT, RIGHT, UP, DOWN};

class ControlScheme{
public:
    virtual std::map<CommandNames, Command*> GetControlCommands() = 0;
    virtual bool is_initialised() = 0;
};