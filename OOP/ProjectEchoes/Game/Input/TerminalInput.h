#pragma once
#include "Input.h"
#include "../ControlSchemes/KeyboardControl.h"

class TerminalInput: public Input{
private:
    std::string Current_command;
    ControlScheme* CurrentCS;
    std::pair<unsigned int, Command*> Last_used_command;

    void set_control_scheme();
public:
    TerminalInput();
    void read_command();
    std::pair<unsigned int, Command*> get_command();
    ~TerminalInput();
};
