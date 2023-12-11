#include "LooseLog.h"

LooseLog::LooseLog(Mechanics& Controller):ObservedController(Controller){
    update();
}

Point LooseLog::get_position() const{
    return Position;
}

void LooseLog::update(){
    Position = ObservedController.get_position();
}