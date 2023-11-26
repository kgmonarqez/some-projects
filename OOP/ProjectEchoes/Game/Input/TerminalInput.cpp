#include "TerminalInput.h"

TerminalInput::TerminalInput():CurrentCS(nullptr){
    set_control_scheme();
}

void TerminalInput::set_control_scheme(){
    std::ifstream f(std::string(std::filesystem::current_path()) + std::string("/../ProjectEchoes/Game/settings.txt"));
    if(f.is_open()){
        std::string tmp;
        while(std::getline(f, tmp)){
            std::istringstream subtmp(tmp);
            std::string token;
            std::getline(subtmp, token, ':');
            if(token == "ControlScheme"){
                std::getline(subtmp, token, ':');
                if(token == "Keyboard"){
                    CurrentCS = new KeyboardControl;
                    break;
                }
                else if(token == "Gamepad"){
                    //example
                    break;
                }
            }
        }
        f.close();
        if(!CurrentCS){
            std::cout << "Incorrect control scheme type\nAutomatically switched to keyboard\n";
            CurrentCS = new KeyboardControl;
        }
    }
}

void TerminalInput::read_command(){
    std::getline(std::cin, Current_command);
}

Command* TerminalInput::get_command(){
    read_command();
    std::map<unsigned int, Command*> Commands = CurrentCS->get_commands();
 
    if(Current_command == "quit"){return new Quit;}
    else if(Commands[*Current_command.c_str()]){return Commands[*Current_command.c_str()];}
    return nullptr;
}

TerminalInput::~TerminalInput(){
    if(CurrentCS){delete CurrentCS;}
}