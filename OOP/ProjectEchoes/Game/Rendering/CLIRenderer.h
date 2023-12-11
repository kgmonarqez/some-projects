#ifndef CLIRENDERER_H
#define CLIRENDERER_H
#include "Renderer.h"
#include "../../Player/Mechanics.h"

class Cell;
class Event;

class CLIRenderer: public Renderer{
private:
    char define_event(Cell& Current_cell);
    std::string define_event_message(Cell& Current_cell, Event*& Current_event);
public:
    void render(Field& Map, Point Position, Event* Current_event, int Current_hp);
};
#endif