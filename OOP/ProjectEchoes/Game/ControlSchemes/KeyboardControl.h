#pragma once
#include <map>
#include <iostream>

#include "ControlScheme.h"

class KeyboardControl: public ControlScheme{
private:
    enum class DefaultCommands{
        LEFT = 'a',
        RIGHT = 'd',
        UP = 'w',
        DOWN = 's'
    };
    std::map<unsigned int, Command*> Commands;
    std::map<CommandNames, unsigned int> CommandDict;
    std::map<std::string, CommandNames> CommandReader{
        {"Left", CommandNames::LEFT}, {"Right", CommandNames::RIGHT}, {"Up", CommandNames::UP}, {"Down", CommandNames::DOWN}
    };

    void set_default_commands();
    void set_settings_commands();
    bool is_initialised();
    void delete_commands();
public:
    KeyboardControl();
    std::map<unsigned int, Command*> get_commands();
    ~KeyboardControl();
};