#include "Finish.h"

bool Finish::action(Mechanics& Controller){
    return false;
}

Finish* Finish::copy(){
    return new Finish(*this);
}