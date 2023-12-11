#include "UnidentifiedCommandLog.h"

UnidentifiedCommandLog::UnidentifiedCommandLog(Input*& InputSystem):ObservedInputSystem(InputSystem){
    update();
}


unsigned int UnidentifiedCommandLog::get_key() const{
    return Key;
}

void UnidentifiedCommandLog::update(){
    Key = std::get<unsigned int>(ObservedInputSystem->get_command());
}