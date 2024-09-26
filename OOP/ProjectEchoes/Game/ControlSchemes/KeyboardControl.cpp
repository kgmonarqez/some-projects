#include "KeyboardControl.h"

KeyboardControl::KeyboardControl(){
    set_settings_commands();
    if(!is_initialised()){
        std::cout << "Incorrect keybinds in settings.txt\nAutomatically switched to default keybinds(WASD)\n";
        delete_commands();
        set_default_commands();
    }
}

std::map<unsigned int, Command*> KeyboardControl::get_commands(){
    return Commands;
}

bool KeyboardControl::is_initialised(){
    return Commands.count(CommandDict[CommandNames::LEFT]) && Commands.count(CommandDict[CommandNames::RIGHT]) && Commands.count(CommandDict[CommandNames::UP]) && Commands.count(CommandDict[CommandNames::DOWN]);
}

void KeyboardControl::set_settings_commands(){
    std::ifstream f(std::string(std::filesystem::current_path()) + std::string("/../ProjectEchoes/Game/settings.txt"));
    if(f.is_open()){
        std::string tmp;
        while(std::getline(f, tmp)){
            std::istringstream subtmp(tmp);
            std::string token;
            std::string Key;
            std::getline(subtmp, token, ':');
            std::getline(subtmp, Key, ':');
            if(CommandReader.count(token)){
                if(CommandReader[token] == CommandNames::LEFT && !CommandDict.count(CommandNames::LEFT) && !Commands.count(*Key.c_str())){
                    CommandDict[CommandNames::LEFT] = *Key.c_str();
                    Commands[*Key.c_str()] = new Left;
                }
                else if(CommandReader[token] == CommandNames::RIGHT && !CommandDict.count(CommandNames::RIGHT) && !Commands.count(*Key.c_str())){
                    CommandDict[CommandNames::RIGHT] = *Key.c_str();
                    Commands[*Key.c_str()] = new Right;
                }
                else if(CommandReader[token] == CommandNames::UP && !CommandDict.count(CommandNames::UP) && !Commands.count(*Key.c_str())){
                    CommandDict[CommandNames::UP] = *Key.c_str();
                    Commands[*Key.c_str()] = new Up;
                }
                else if(CommandReader[token] == CommandNames::DOWN && !CommandDict.count(CommandNames::DOWN) && !Commands.count(*Key.c_str())){
                    CommandDict[CommandNames::DOWN] = *Key.c_str();
                    Commands[*Key.c_str()] = new Down;
                }
            }
        }
        f.close();
    }
}

void KeyboardControl::set_default_commands(){
    Commands[static_cast<unsigned int>(DefaultCommands::LEFT)] = new Left;
    Commands[static_cast<unsigned int>(DefaultCommands::RIGHT)] = new Right;
    Commands[static_cast<unsigned int>(DefaultCommands::UP)] = new Up;
    Commands[static_cast<unsigned int>(DefaultCommands::DOWN)] = new Down;
}

void KeyboardControl::delete_commands(){
    if(Commands[CommandDict[CommandNames::LEFT]]){
        delete Commands[CommandDict[CommandNames::LEFT]];
        Commands.erase(CommandDict[CommandNames::LEFT]);
        CommandDict.erase(CommandNames::LEFT);
    }
    if(Commands[CommandDict[CommandNames::RIGHT]]){
        delete Commands[CommandDict[CommandNames::RIGHT]];
        Commands.erase(CommandDict[CommandNames::RIGHT]);
        CommandDict.erase(CommandNames::RIGHT);
    }
    if(Commands[CommandDict[CommandNames::UP]]){
        delete Commands[CommandDict[CommandNames::UP]];
        Commands.erase(CommandDict[CommandNames::UP]);
        CommandDict.erase(CommandNames::UP);
    }
    if(Commands[CommandDict[CommandNames::DOWN]]){
        delete Commands[CommandDict[CommandNames::DOWN]];
        Commands.erase(CommandDict[CommandNames::DOWN]);
        CommandDict.erase(CommandNames::DOWN);
    }
}

KeyboardControl::~KeyboardControl(){
    delete_commands();
}