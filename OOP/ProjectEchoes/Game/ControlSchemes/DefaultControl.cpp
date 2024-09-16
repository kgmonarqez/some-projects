#include "DefaultControl.h"

DefaultControl::DefaultControl(){
ControlCommands[CommandNames::LEFT] = new Left(static_cast<char>(DefaultCommands::LEFT));
ControlCommands[CommandNames::RIGHT] = new Right(static_cast<char>(DefaultCommands::RIGHT));
ControlCommands[CommandNames::UP] = new Up(static_cast<char>(DefaultCommands::UP));
ControlCommands[CommandNames::DOWN] = new Down(static_cast<char>(DefaultCommands::DOWN));
}

std::map<CommandNames, Command*> DefaultControl::GetControlCommands(){
    return ControlCommands;
}

bool DefaultControl::is_initialised(){
    return ControlCommands[CommandNames::LEFT] && ControlCommands[CommandNames::RIGHT] && ControlCommands[CommandNames::UP] && ControlCommands[CommandNames::DOWN];
}

DefaultControl::~DefaultControl(){
    if(ControlCommands[CommandNames::LEFT]){delete ControlCommands[CommandNames::LEFT];}
    if(ControlCommands[CommandNames::RIGHT]){delete ControlCommands[CommandNames::RIGHT];}
    if(ControlCommands[CommandNames::UP]){delete ControlCommands[CommandNames::UP];}
    if(ControlCommands[CommandNames::DOWN]){delete ControlCommands[CommandNames::DOWN];}
}