#pragma once
#include "ControlSchemes/SettingsControl.h"
#include "ControlSchemes/TerminalControl.h"
#include "ControlSchemes/DefaultControl.h"
#include "../Player/Mechanics.h"

class KeyboardInput{
private:
    ControlScheme* CurrentCS;
public:
    KeyboardInput();
    ~KeyboardInput();

    std::string console();
    ControlScheme* choose_control_scheme(std::string Input_command);
    void action(std::string Input_command, Mechanics& Controller);
    bool change_control_scheme(std::string Input_command);
};
