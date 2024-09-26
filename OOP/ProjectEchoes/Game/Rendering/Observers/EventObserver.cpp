#include "EventObserver.h"

EventObserver::EventObserver(RenderingWatcher& RW, Mechanics& Controller, Field& Map):Master(RW), ObservedController(Controller), ObservedMap(Map){}

void EventObserver::update(){
    Event* tmp = ObservedMap.get_cell(ObservedController.get_position().get_x(), ObservedController.get_position().get_y()).get_event();
    if(tmp){
        Master.update_event(tmp->copy());
    }
    else{
        Master.update_event(nullptr);
    }
}