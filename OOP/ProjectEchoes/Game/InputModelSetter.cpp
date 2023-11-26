#include "InputModelSetter.h"

Input* InputModelSetter::set_input_model(){
    Input* InputModel = nullptr;
    std::ifstream f(std::string(std::filesystem::current_path()) + std::string("/../ProjectEchoes/Game/settings.txt"));
    if(f.is_open()){
        std::string tmp;
        while(std::getline(f, tmp)){
            std::istringstream subtmp(tmp);
            std::string token;
            std::getline(subtmp, token, ':');
            if(token == "InputModel"){
                std::getline(subtmp, token, ':');
                if(token == "Terminal"){
                    InputModel = new TerminalInput;
                    break;
                }
                else if(token == "File"){
                    //example
                    break;
                }
                else if(token == "Remote"){
                    //example
                    break;
                }
            }
        }
        f.close();
        if(!InputModel){
            std::cout << "Incorrect input model\nAutomatically switched to terminal\n";
            InputModel = new TerminalInput;
        }
    }
    return InputModel;
}