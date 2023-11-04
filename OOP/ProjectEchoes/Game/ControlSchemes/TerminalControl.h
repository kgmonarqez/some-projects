#pragma once
#include "ControlScheme.h"

class TerminalControl: public ControlScheme{
private:
    std::map<CommandNames, Command*> ControlCommands;
    char read_key();
public:
    TerminalControl();
    std::map<CommandNames, Command*> GetControlCommands();
    bool is_initialised();
    bool is_key_used(char Check_key);
    ~TerminalControl();
};