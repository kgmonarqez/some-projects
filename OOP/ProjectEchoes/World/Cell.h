#ifndef CELL_H
#define CELL_H
#include "../Events/Event.h"

class Event;

class Cell{
private:
    bool Passing;
    Event* Current_event;
public:
    Cell(bool Input_passing=true, Event* Input_event=nullptr);
    Cell(const Cell& Copy);
    Cell(Cell&& Move);
    ~Cell();

    Cell& operator=(const Cell& Copy);
    Cell& operator=(Cell&& Move);

    void set_passing(bool Input_passing);
    void set_event(Event* Input_event=nullptr);

    bool get_passing();
    Event* get_event();
};
#endif