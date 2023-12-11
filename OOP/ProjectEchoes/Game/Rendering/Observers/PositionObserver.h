#pragma once
#include "MechanicsObserver.h"
#include "../RenderingWatcher.h"

class RenderingWatcher;

class PositionObserver: public MechanicsObserver{
private:
    RenderingWatcher& Master;
    Mechanics& ObservedController;
public:
    PositionObserver(RenderingWatcher& RW, Mechanics& Controller);
    void update();
};