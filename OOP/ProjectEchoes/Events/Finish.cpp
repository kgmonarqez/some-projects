#include "Finish.h"

bool Finish::action(Mechanics& Controller){
    return true;
}

Finish* Finish::copy(){
    return new Finish(*this);
}