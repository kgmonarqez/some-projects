#include "RenderingWatcher.h"

RenderingWatcher::RenderingWatcher():Current_event(nullptr), R(new CLIRenderer){}

RenderingWatcher::~RenderingWatcher(){
    if(Current_event){delete Current_event;}
    if(R){delete R;}
}

void RenderingWatcher::update_position(Point New_position){
    Current_position = New_position; 
}

void RenderingWatcher::update_event(Event* New_event){
    if(Current_event){delete Current_event;}
    Current_event = New_event;
}

void RenderingWatcher::update_hp(int New_hp){
    Current_hp = New_hp;
}

void RenderingWatcher::call_renderer(Field& Map){
    R->render(Map, Current_position, Current_event, Current_hp);
}