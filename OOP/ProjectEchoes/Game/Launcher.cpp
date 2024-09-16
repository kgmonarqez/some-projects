#include "Launcher.h"

Launcher::Launcher(){
    Generator Gen;
    std::cout << "Select level: ";
    int Current_level_num = std::atoi(KI.console().c_str());
    Field Map = Gen.level_select(Current_level_num);
    Player User{};
    Mechanics Controller{User, Map};
    std::cout << "Level " << Current_level_num << '\n';
    std::string tmp = KI.console();
    while(tmp != "quit"){
        KI.action(tmp, Controller);
        if(!User.check_hp() && !ask_for_replay()){
            break;
        }
        if(Controller.is_finish()){
            if(Current_level_num + 1 <= LAST_LEVEL_NUM){
                Map = Gen.level_select(++Current_level_num);
                Controller.player_restore();
                Controller.set_position(Map.get_start());
            }
            else{
                break;
            }
        }
        tmp = KI.console();
    }
}

bool Launcher::ask_for_replay(){
    std::cout << "Continue?\n[Y/Yes, N/No]: ";
    std::string tmp;
    bool res;
    while(tmp != "Y" && tmp != "Yes" && tmp != "N" && tmp != "No"){
        tmp = KI.console();
        if(tmp == "Y" || tmp == "Yes"){
            res = true;
        }
        else if(tmp == "N" || tmp == "No"){
            res = false;
        }
        else{
            tmp = KI.console();
        }
    }
    return res;
}
//std::cout << "\x1B[2J\x1B[H";