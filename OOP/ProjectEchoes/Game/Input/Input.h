#pragma once
#include <iostream>
#include <map>

#include "../ControlSchemes/KeyboardControl.h"

class Input{
public:
    virtual void read_command() = 0;
    virtual Command* get_command() = 0;
};