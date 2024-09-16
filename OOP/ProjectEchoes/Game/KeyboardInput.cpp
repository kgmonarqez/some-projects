#include "KeyboardInput.h"

KeyboardInput::KeyboardInput():CurrentCS(nullptr){
    while(!CurrentCS){
        std::cout << "Choose control scheme: ";
        std::string tmp = console();
        CurrentCS = choose_control_scheme(tmp);
        if(CurrentCS && !CurrentCS->is_initialised()){
            std::cout << "This control scheme is incorrect\n";
            delete CurrentCS;
            CurrentCS = nullptr;
        }
    }
}

KeyboardInput::~KeyboardInput(){
    if(CurrentCS){delete CurrentCS;}
}

std::string KeyboardInput::console(){
    std::string tmp;
    std::getline(std::cin, tmp);
    return tmp;
}

ControlScheme* KeyboardInput::choose_control_scheme(std::string Input_command){
    ControlScheme* CS = nullptr;
    if(Input_command == "file"){CS = new SettingsControl;}
    else if(Input_command == "CLI" || Input_command == "cli"){CS = new TerminalControl;}
    else if(Input_command == "default"){CS = new DefaultControl;}
    return CS;
}

void KeyboardInput::action(std::string Input_command, Mechanics& Controller){
    if(!change_control_scheme(Input_command)){
        std::map<CommandNames, Command*> tmplist = CurrentCS->GetControlCommands();
        for(size_t i = 0; i < Input_command.size(); i++){
            char Key = Input_command.c_str()[i];
            if(Key == tmplist[CommandNames::LEFT]->get_key()){
                tmplist[CommandNames::LEFT]->action(Controller);
            }
            else if(Key == tmplist[CommandNames::RIGHT]->get_key()){
                tmplist[CommandNames::RIGHT]->action(Controller);
            }
            else if(Key == tmplist[CommandNames::UP]->get_key()){
                tmplist[CommandNames::UP]->action(Controller);
            }
            else if(Key == tmplist[CommandNames::DOWN]->get_key()){
                tmplist[CommandNames::DOWN]->action(Controller);
            }
            else{
                break;
            }
        }
    }
}

bool KeyboardInput::change_control_scheme(std::string Input_command){
    std::istringstream tmp(Input_command);
    std::string token;
    std::getline(tmp, token, ' ');
    ControlScheme* CS = nullptr;
    if(token == "cs-change"){
        std::getline(tmp, token, ' ');
        CS = choose_control_scheme(token);
        if(CS->is_initialised()){
            delete CurrentCS;
            CurrentCS = CS;
        }
        else{
            delete CS;
        }
        return true;
    }
    else{
        return false;
    }
}