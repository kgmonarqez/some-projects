#pragma once
#include "Field.h"
#include "../Events/SpikeDamage.h"
#include "../Events/Heal.h"
#include "../Events/Teleport.h"
#include "../Events/Finish.h"
#include "Level.h"

class Field;

class Generator{
private:
    enum class Symbols{
        WALL = '#',
        SPIKE = 'x',
        HEAL = 'H',
        START = 'S',
        FINISH = 'F',
        PORTAL = '0',
        EMPTY_CELL = '.'
    };

    Field level_generator(std::string Level_name);
    void setting_events(Field& Map, Level& This_level);
    void setting_portals(Field& Map, Level& This_level);
public:
    Field level_select(int Level_num);
};