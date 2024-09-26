#pragma once
#include "MechanicsObserver.h"
#include "../RenderingWatcher.h"

class RenderingWatcher;

class EventObserver: public MechanicsObserver{
private:
    RenderingWatcher& Master;
    Mechanics& ObservedController;
    Field& ObservedMap;
public:
    EventObserver(RenderingWatcher& RW, Mechanics& Controller, Field& Map);
    void update();
};