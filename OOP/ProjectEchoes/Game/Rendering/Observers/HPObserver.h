#pragma once
#include "MechanicsObserver.h"
#include "../RenderingWatcher.h"

class RenderingWatcher;

class HPObserver: public MechanicsObserver{
private:
    RenderingWatcher& Master;
    Player& ObservedPlayer;
public:
    HPObserver(RenderingWatcher& RW, Player& Entity);
    void update();
};