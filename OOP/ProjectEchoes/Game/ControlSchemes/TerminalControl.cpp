#include "TerminalControl.h"

TerminalControl::TerminalControl(){
    std::cout << "Left: ";
    char Key;
    Key = read_key();
    if(!is_key_used(Key)){ControlCommands[CommandNames::LEFT] = new Left(Key);}
    std::cout << "Right: ";
    Key = read_key();
    if(!is_key_used(Key)){ControlCommands[CommandNames::RIGHT] = new Right(Key);}
    std::cout << "Up: ";
    Key = read_key();
    if(!is_key_used(Key)){ControlCommands[CommandNames::UP] = new Up(Key);}
    std::cout << "Down: ";
    Key = read_key();
    if(!is_key_used(Key)){ControlCommands[CommandNames::DOWN] = new Down(Key);}
}

std::map<CommandNames, Command*> TerminalControl::GetControlCommands(){
    return ControlCommands;
}

bool TerminalControl::is_initialised(){
    return ControlCommands[CommandNames::LEFT] && ControlCommands[CommandNames::RIGHT] && ControlCommands[CommandNames::UP] && ControlCommands[CommandNames::DOWN];
}

bool TerminalControl::is_key_used(char Check_key){
    return (ControlCommands.count(CommandNames::LEFT) && ControlCommands[CommandNames::LEFT]->get_key() == Check_key) 
    || (ControlCommands.count(CommandNames::RIGHT) && ControlCommands[CommandNames::RIGHT]->get_key() == Check_key)
    || (ControlCommands.count(CommandNames::UP) && ControlCommands[CommandNames::UP]->get_key() == Check_key)
    || (ControlCommands.count(CommandNames::DOWN) && ControlCommands[CommandNames::DOWN]->get_key() == Check_key);
}

TerminalControl::~TerminalControl(){
    if(ControlCommands[CommandNames::LEFT]){delete ControlCommands[CommandNames::LEFT];}
    if(ControlCommands[CommandNames::RIGHT]){delete ControlCommands[CommandNames::RIGHT];}
    if(ControlCommands[CommandNames::UP]){delete ControlCommands[CommandNames::UP];}
    if(ControlCommands[CommandNames::DOWN]){delete ControlCommands[CommandNames::DOWN];}
}

char TerminalControl::read_key(){
    std::string tmp;
    std::getline(std::cin, tmp);
    return *tmp.c_str();
}