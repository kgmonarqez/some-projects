#include "Heal.h"

bool Heal::action(Mechanics& Controller){
    Controller.healing(HEAL_POINTS);
    return true;
}

Heal* Heal::copy(){
    return new Heal(*this);
}

char Heal::get_representation(){
    return 'H';
}