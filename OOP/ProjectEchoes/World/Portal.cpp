#include "Portal.h"

Portal::Portal(Point Input_entrance, Point Input_exit):Entrance(Input_entrance), Exit(Input_exit){}

Point Portal::get_entrance(){
    return Entrance;
}

Point Portal::get_exit(){
    return Exit;
}