#pragma once
#include "Player.h"
#include "../World/Point.h"
#include "../World/Field.h"
#include "../World/Cell.h"
#include "../Events/Event.h"

enum class pathes {RIGHT, LEFT, UP, DOWN};

class Player;
class Point;
class Field;
class Cell;
class Event;


class Mechanics{
private:
    Point Position;
    Player& Entity;
    Field& Map;

    void step(int x, int y);
    void event_activator();
public:
    Mechanics(Player& Bindable_entity, Field& Bindable_map);

    void movement(pathes Path);
    
    void damage_receiving(int Damage);
    void healing(int Heal_points);
    
    void mana_spending(int Spell_cost);
    void mana_receiving(int Mana_points);

    void scores_changing(int Scores_points);

    void set_position(Point New_position);

    void player_restore();

    bool is_finish();
};