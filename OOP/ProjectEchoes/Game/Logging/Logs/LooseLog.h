#pragma once
#include "Log.h"
#include "../../../Player/Mechanics.h"

class LooseLog: public Log{
private:
    Mechanics& ObservedController;
    
    Point Position;
public:
    LooseLog(Mechanics& Controller);
    Point get_position() const;

    void update();
};