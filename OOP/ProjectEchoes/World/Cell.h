#pragma once
#include "../Events/Event.h"

class Event;

class Cell{
private:
    bool Passing;
    Event* Current_event;
public:
    Cell(bool Input_passing=true, Event* Input_event=nullptr);

    void set_passing(bool Input_passing);
    void set_event(Event* Input_event);

    bool get_passing();
    Event* get_event();
};