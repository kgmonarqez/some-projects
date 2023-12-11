#include "HPObserver.h"

HPObserver::HPObserver(RenderingWatcher& RW, Player& Entity):Master(RW), ObservedPlayer(Entity){}

void HPObserver::update(){
    Master.update_hp(ObservedPlayer.get_hp());
}