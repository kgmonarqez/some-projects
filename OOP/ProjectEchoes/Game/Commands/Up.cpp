#include "Up.h"

Up::Up(char Settings_key):Key(Settings_key){}

void Up::action(Mechanics& Controller){
    Controller.movement(pathes::UP);
}

char Up::get_key(){
    return Key;
}
