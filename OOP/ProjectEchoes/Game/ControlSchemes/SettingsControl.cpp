#include "SettingsControl.h"

SettingsControl::SettingsControl(){
    std::ifstream f(std::string(std::filesystem::current_path()) + std::string("/../ProjectEchoes/Game/settings.txt"));
    if(f.is_open()){
        std::string tmp;
        while(std::getline(f, tmp)){
            std::istringstream subtmp(tmp);
            std::string token;
            std::getline(subtmp, token, ':');
            if(token == "Left" && !ControlCommands.count(CommandNames::LEFT)){
                std::getline(subtmp, token, ':');
                if(!is_key_used(*token.c_str())){ControlCommands[CommandNames::LEFT] = new Left(*token.c_str());}
            }
            else if(token == "Right" && !ControlCommands.count(CommandNames::RIGHT)){
                std::getline(subtmp, token, ':');
                if(!is_key_used(*token.c_str())){ControlCommands[CommandNames::RIGHT] = new Right(*token.c_str());}
            }
            else if(token == "Up" && !ControlCommands.count(CommandNames::UP)){
                std::getline(subtmp, token, ':');
                if(!is_key_used(*token.c_str())){ControlCommands[CommandNames::UP] = new Up(*token.c_str());}
            }
            else if(token == "Down" && !ControlCommands.count(CommandNames::DOWN)){
                std::getline(subtmp, token, ':');
                if(!is_key_used(*token.c_str())){ControlCommands[CommandNames::DOWN] = new Down(*token.c_str());}
            }
        }
        f.close();
    }
}

bool SettingsControl::is_key_used(char Check_key){
    return (ControlCommands.count(CommandNames::LEFT) && ControlCommands[CommandNames::LEFT]->get_key() == Check_key) 
    || (ControlCommands.count(CommandNames::RIGHT) && ControlCommands[CommandNames::RIGHT]->get_key() == Check_key)
    || (ControlCommands.count(CommandNames::UP) && ControlCommands[CommandNames::UP]->get_key() == Check_key)
    || (ControlCommands.count(CommandNames::DOWN) && ControlCommands[CommandNames::DOWN]->get_key() == Check_key);
}

std::map<CommandNames, Command*> SettingsControl::GetControlCommands(){
    return ControlCommands;
}

bool SettingsControl::is_initialised(){
    return ControlCommands[CommandNames::LEFT] && ControlCommands[CommandNames::RIGHT] && ControlCommands[CommandNames::UP] && ControlCommands[CommandNames::DOWN];
}

SettingsControl::~SettingsControl(){
    if(ControlCommands[CommandNames::LEFT]){delete ControlCommands[CommandNames::LEFT];}
    if(ControlCommands[CommandNames::RIGHT]){delete ControlCommands[CommandNames::RIGHT];}
    if(ControlCommands[CommandNames::UP]){delete ControlCommands[CommandNames::UP];}
    if(ControlCommands[CommandNames::DOWN]){delete ControlCommands[CommandNames::DOWN];}
}