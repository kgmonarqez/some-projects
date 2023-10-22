#include "Teleport.h"

Teleport::Teleport(Point Input_destination){
    Destination = Input_destination;
}

void Teleport::action(Mechanics& Controller){
    Controller.set_position(Destination);
}