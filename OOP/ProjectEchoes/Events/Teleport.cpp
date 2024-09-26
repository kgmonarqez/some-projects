#include "Teleport.h"

Teleport::Teleport(Point Input_destination){
    Destination = Input_destination;
}

bool Teleport::action(Mechanics& Controller){
    Controller.set_position(Destination);
    return false;
}

Teleport* Teleport::copy(){
    return new Teleport(*this);
}