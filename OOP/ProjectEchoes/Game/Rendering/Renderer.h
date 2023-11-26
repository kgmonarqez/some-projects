#ifndef RENDERER_H
#define RENDERER_H
#include "../../World/Field.h"
#include <iostream>

class Field;

class Renderer{
public:
    virtual void render(Field& Map, Player& Entity, Point Position) = 0;
};
#endif