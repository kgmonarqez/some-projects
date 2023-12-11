#ifndef MECHANICS_H
#define MECHANICS_H
#include <list>
#include "Player.h"
#include "../World/Point.h"
#include "../World/Field.h"
#include "../World/Cell.h"
#include "../Events/Event.h"
#include "../Game/Rendering/Observers/MechanicsObserver.h"

enum class pathes {RIGHT, LEFT, UP, DOWN};

class Player;
class Point;
class Field;
class Cell;
class Event;
class MechanicsObserver;

class Mechanics{
private:
    Player& Entity;
    Field& Map;

    Point Position;

    std::list<MechanicsObserver*> Observers;

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

    void restore();

    bool is_finish();

    void add(MechanicsObserver* Ref);
    void remove(MechanicsObserver* Ref);
    void notification();

    Point get_position();
};
#endif