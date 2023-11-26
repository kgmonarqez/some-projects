#pragma once
#include "Input.h"
#include "../ControlSchemes/KeyboardControl.h"

class TerminalInput: public Input{
private:
    std::string Current_command;
    ControlScheme* CurrentCS;

    void set_control_scheme();
public:
    TerminalInput();
    void read_command();
    Command* get_command();
    std::map<CommandNames, Command*> get_command_list();
    ~TerminalInput();
};
