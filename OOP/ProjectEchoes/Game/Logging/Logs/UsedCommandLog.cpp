#include "UsedCommandLog.h"

UsedCommandLog::UsedCommandLog(Input*& InputSystem):ObservedInputSystem(InputSystem){
    update();
}

std::pair<unsigned int, Command*> UsedCommandLog::get_command() const{
    return Used_command;
}

void UsedCommandLog::update(){
    Used_command = ObservedInputSystem->get_command();
}