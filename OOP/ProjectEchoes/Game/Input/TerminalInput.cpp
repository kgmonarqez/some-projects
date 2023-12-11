#include "TerminalInput.h"

TerminalInput::TerminalInput():CurrentCS(nullptr), Last_used_command(std::pair<unsigned int, Command*>{0, nullptr}){
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
    std::map<unsigned int, Command*> Commands = CurrentCS->get_commands();

    if(Current_command == "quit"){Last_used_command = std::pair<unsigned int, Command*>{0, new Quit};}
    else if(Commands[*Current_command.c_str()]){Last_used_command = std::pair<unsigned int, Command*>{*Current_command.c_str(), Commands[*Current_command.c_str()]};}
    else{Last_used_command = std::pair<unsigned int, Command*>{*Current_command.c_str(), nullptr};}
}

std::pair<unsigned int, Command*> TerminalInput::get_command(){
    return Last_used_command;
}

TerminalInput::~TerminalInput(){
    if(CurrentCS){delete CurrentCS;}
}