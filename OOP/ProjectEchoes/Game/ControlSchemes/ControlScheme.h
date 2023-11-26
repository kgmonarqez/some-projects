#pragma once
#include <fstream>
#include <filesystem>

#include "../Commands/Left.h"
#include "../Commands/Right.h"
#include "../Commands/Up.h"
#include "../Commands/Down.h"
#include "../Commands/Quit.h"

enum class CommandNames{LEFT, RIGHT, UP, DOWN, QUIT};

class ControlScheme{
public:
    virtual std::map<unsigned int, Command*> get_commands() = 0;
};