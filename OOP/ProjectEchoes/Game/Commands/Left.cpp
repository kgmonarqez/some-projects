#include "Left.h"

Left::Left(char Settings_key):Key(Settings_key){}

void Left::action(Mechanics& Controller){
    Controller.movement(pathes::LEFT);
}

char Left::get_key(){
    return Key;
}