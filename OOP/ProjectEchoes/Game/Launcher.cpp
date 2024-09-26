#include "Launcher.h"
#include "Rendering/Observers/EventObserver.h"
#include "Rendering/Observers/PositionObserver.h"
#include "Rendering/Observers/HPObserver.h"
#include "Logging/OstreamOverload.h"
#include "Logging/LoggingManager.h"

Launcher::Launcher():InputModel(nullptr){}

void Launcher::run(){
    InputModelSetter IMS;
    InputModel = IMS.set_input_model();
    
    Generator Gen;
    std::cout << "\x1B[2J\x1B[H";
    std::cout << "Select level: ";
    std::string tmp;
    std::getline(std::cin, tmp);
    int Current_level_num = std::atoi(tmp.c_str());
    if(Current_level_num < 1){Current_level_num = 1;}
    
    Field Map = Gen.level_select(Current_level_num);
    Player User{};
    Mechanics Controller{User, Map};

    LoggingManager LManager{Controller, User, Map, InputModel};

    Controller.add(new HPObserver(RW, User));
    Controller.add(new PositionObserver(RW, Controller));
    Controller.add(new EventObserver(RW, Controller, Map));
    
    LManager.add_log(LogNames::NEW_GAME);
    std::pair<unsigned int, Command*> Current_command{0, nullptr};
    while(!dynamic_cast<Quit*>(std::get<Command*>(Current_command))){
        if(std::get<Command*>(Current_command)){
            std::get<Command*>(Current_command)->action(Controller);
            if(std::get<unsigned int>(Current_command)){LManager.add_log(LogNames::USED_COMMAND);}
        }
        else{
            if(std::get<unsigned int>(Current_command)){LManager.add_log(LogNames::UNIDENTIFIED_COMMAND);}
        }
        if(!User.check_hp()){
            RW.call_renderer(Map);
            LManager.add_log(LogNames::LOOSE);
            if(!ask_for_replay()){
                break;
            }
            else{
                Map = Gen.level_select(Current_level_num);
                Controller.restore();
                Controller.set_position(Map.get_start());
                LManager.add_log(LogNames::NEW_GAME);
            }
        }
        if(Controller.is_finish()){
            RW.call_renderer(Map);
            LManager.add_log(LogNames::WIN);
            LManager.call_loggers();
            if(Current_level_num + 1 <= LAST_LEVEL_NUM){
                std::getline(std::cin, tmp);
                Map = Gen.level_select(++Current_level_num);
                Controller.restore();
                Controller.set_position(Map.get_start());
                LManager.add_log(LogNames::NEW_GAME);
            }
            else{
                std::getline(std::cin, tmp);
                std::cout << "The end\n";
                break;
            }
        }
        RW.call_renderer(Map);
        LManager.call_loggers();
        InputModel->read_command();
        Current_command = InputModel->get_command();
    }
    LManager.add_log(LogNames::QUIT);
    LManager.call_loggers();
}

bool Launcher::ask_for_replay(){
    std::string tmp;
    bool res;
    while(tmp != "Y" && tmp != "Yes" && tmp != "N" && tmp != "No"){
        std::getline(std::cin, tmp);
        if(tmp == "Y" || tmp == "Yes"){
            res = true;
        }
        else if(tmp == "N" || tmp == "No"){
            res = false;
        }
    }
    return res;
}