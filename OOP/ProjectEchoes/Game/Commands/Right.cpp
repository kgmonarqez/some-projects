#include "Right.h"

Right::Right(char Settings_key):Key(Settings_key){}

void Right::action(Mechanics& Controller){
    Controller.movement(pathes::RIGHT);
}

char Right::get_key(){
    return Key;
}
