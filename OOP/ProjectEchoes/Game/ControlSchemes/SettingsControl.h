#pragma once
#include "ControlScheme.h"
#include <fstream>
#include <filesystem>

class SettingsControl: public ControlScheme{
private:
    std::map<CommandNames, Command*> ControlCommands;
    bool is_key_used(char Check_key);
public:
    SettingsControl();
    std::map<CommandNames, Command*> GetControlCommands();
    bool is_initialised();
    ~SettingsControl();
};