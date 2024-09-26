#ifndef CLIRENDERER_H
#define CLIRENDERER_H
#include "Renderer.h"
#include "../../Player/Mechanics.h"

class Cell;
class Event;

class CLIRenderer: public Renderer{
private:
    char define_event(Cell& Current_cell);
public:
    void render(Field& Map, Player& Entity, Point Position);
};
#endif