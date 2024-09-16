#include "Down.h"

Down::Down(char Settings_key):Key(Settings_key){}

void Down::action(Mechanics& Controller){
    Controller.movement(pathes::DOWN);
}

char Down::get_key(){
    return Key;
}