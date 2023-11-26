#include "Launcher.h"

Launcher::Launcher():InputModel(nullptr){}

void Launcher::run(){
    InputModelSetter IMS;
    InputModel = IMS.set_input_model();

    Watcher* W = new Watcher;
    
    Generator Gen;
    std::cout << "Select level: ";
    std::string tmp;
    std::getline(std::cin, tmp);
    int Current_level_num = std::atoi(tmp.c_str());
    
    Field Map = Gen.level_select(Current_level_num);
    Player User{};
    Mechanics Controller{User, Map};
    W->update_position(Controller.get_position());
    Controller.set_watcher(W);

    Command* Current_command = nullptr;
    while(!dynamic_cast<Quit*>(Current_command)){
        if(Current_command){Current_command->action(Controller);}
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
        W->call_renderer(Map, User);
        Current_command = InputModel->get_command();
    }
}

bool Launcher::ask_for_replay(){
    std::cout << "Continue?\n[Y/Yes, N/No]: ";
    std::string tmp;
    std::getline(std::cin, tmp);
    bool res;
    while(tmp != "Y" && tmp != "Yes" && tmp != "N" && tmp != "No"){
        if(tmp == "Y" || tmp == "Yes"){
            res = true;
        }
        else if(tmp == "N" || tmp == "No"){
            res = false;
        }
        else{
            std::getline(std::cin, tmp);
        }
    }
    return res;
}