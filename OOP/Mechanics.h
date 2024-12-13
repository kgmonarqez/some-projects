#pragma once
#include "Player.h"
#include "Field.h"
#include "Point.h"

enum class pathes {right, left, up, down};

class Mechanics{
private:
    Point Position;
    Player &Entity;
    Field &Map;

public:
    Mechanics(Player &Bindable_entity, Field &Bindable_map);

    void movement(pathes Path);
    
    void damage_receiving(int Damage);
    void healing(int Heal_points);
    
    void mana_spending(int Spell_cost);
    void mana_receiving(int Mana_points);

    void scores_changing(int Scores_points);
};