#include "Mechanics.h"
#include <iostream>

void Mechanics::step(int x, int y){
    Position.set_x(Position.get_x()+x);
    Position.set_y(Position.get_y()+y);
    event_activator();
}

Mechanics::Mechanics(Player &Bindable_entity, Field &Bindable_map) : Entity(Bindable_entity), Map(Bindable_map){
    Position = Map.get_start();
}

void Mechanics::movement(pathes Path){
    switch(Path){
        case pathes::left: 
            if(Position.get_x()-1 >= 0 && Map.check_passing(Position.get_x()-1, Position.get_y())){
                step(-1, 0);
            }
            break;
        case pathes::right:
            if(Position.get_x()+1 < Map.get_field_size_x() && Map.check_passing(Position.get_x()+1, Position.get_y())){
                step(1, 0);
            }
            break;
        case pathes::up: 
            if(Position.get_y()-1 < Map.get_field_size_y() && Map.check_passing(Position.get_x(), Position.get_y()-1)){
                step(0, -1);
            }
            break;
        case pathes::down: 
            if(Position.get_y()+1 >= 0 && Map.check_passing(Position.get_x(), Position.get_y()+1)){
                step(0, 1);
            }
            break;
    }
}

void Mechanics::damage_receiving(int Damage){
    if(Damage >= 0){
        if(Entity.get_hp() - Damage < 0){
            Entity.set_hp(0);
        }
        else{
            Entity.set_hp(Entity.get_hp() - Damage);
        }
    }
}

void Mechanics::healing(int Heal_points){
    if(Heal_points >= 0){
        if(Entity.get_hp() + Heal_points > DEFAULT_HP){
            Entity.set_hp(DEFAULT_HP);
        }
        else{
            Entity.set_hp(Entity.get_hp() + Heal_points);
        }
    }
}

void Mechanics::mana_spending(int Spell_cost){
    if(Spell_cost >= 0){
        if(Entity.get_mana() - Spell_cost < 0){
            Entity.set_mana(DEFAULT_MANA);
        }
        else{
            Entity.set_mana(Entity.get_mana() - Spell_cost);
        }
    }
}

void Mechanics::mana_receiving(int Mana_points){
    if(Mana_points >= 0){
        if(Entity.get_mana() + Mana_points > DEFAULT_MANA){
            Entity.set_mana(DEFAULT_MANA);
        }
        else{
            Entity.set_mana(Entity.get_mana() - Mana_points);
        }
    }
}

void Mechanics::scores_changing(int Scores_points){
    Entity.set_scores(Entity.get_scores() + Scores_points);
}

void Mechanics::event_activator(){
    Cell& Current_cell = Map.get_cell(Position.get_x(), Position.get_y());
    Event* Current_event = Current_cell.get_event();
    if(Current_event){
        if(Current_event->action(*this)){
            Current_cell.set_event();
        }
    }
}

void Mechanics::set_position(Point New_position){
    Position = New_position;
}