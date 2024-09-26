#pragma once
#include "Log.h"
#include "../../../Player/Mechanics.h"

class NewGameLog: public Log{
private:
    Mechanics& ObservedController;
    Field& ObservedField;
    
    Point Position;
    int Field_size_x;
    int Field_size_y;
public:
    NewGameLog(Mechanics& Controller, Field& Map);
    Point get_position() const;
    int get_field_size_x() const;
    int get_field_size_y() const;

    void update();
};