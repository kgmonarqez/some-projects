#ifndef RENDERER_H
#define RENDERER_H
#include "../../World/Field.h"
#include <iostream>

class Field;
class Event;

class Renderer{
public:
    virtual void render(Field& Map, Point Position, Event* Current_event, int New_hp) = 0;
};
#endif