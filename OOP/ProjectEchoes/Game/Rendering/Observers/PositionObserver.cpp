#include "PositionObserver.h"

PositionObserver::PositionObserver(RenderingWatcher& RW, Mechanics& Controller):Master(RW), ObservedController(Controller){}

void PositionObserver::update(){
    Master.update_position(ObservedController.get_position());
}