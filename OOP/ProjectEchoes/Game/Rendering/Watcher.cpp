#include "Watcher.h"

Watcher::Watcher():Current_event(nullptr), R(new CLIRenderer){}

Watcher::~Watcher(){
    if(Current_event){delete Current_event;}
    if(R){delete R;}
}

void Watcher::update_position(Point New_position){
    Current_position = New_position;
}

void Watcher::update_event(Event* New_event){
    if(Current_event){
        delete Current_event;
        Current_event = nullptr;
    }
    if(New_event){
        Current_event = New_event->copy();
    }
}

void Watcher::call_renderer(Field& Map, Player& Entity){
    R->render(Map, Entity, Current_position);
}