#pragma once
#include "Field.h"
#include "../Events/SpikeDamage.h"
#include "../Events/Heal.h"
#include "../Events/Teleport.h"
#include "../Events/Finish.h"

class Field;

enum class Symbols{
    WALL = '#',
    SPIKE = 'x',
    HEAL = 'H',
    START = 'S',
    FINISH = 'F',
    PORTAL = '0',
    EMPTY_CELL = '.'
};

class Generator{
public:
    Field level_generator(int Level_num);
    
    Field level1_generation();
    Field level2_generation();
};