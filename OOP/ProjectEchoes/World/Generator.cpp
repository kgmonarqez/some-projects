#include "Generator.h"

Field Generator::level_select(int Level_num){
    switch(Level_num){
        case 1:
            return level_generator("Level_1/1.txt");
        case 2:
            return level_generator("Level_2/1.txt");
        default:
            return level_generator("Level_1/1.txt");
    }
}

Field Generator::level_generator(std::string Level_path){
    Level This_level(Level_path);

    Field Map = Field(This_level.get_size_x(), This_level.get_size_y());
    setting_events(Map, This_level);
    setting_portals(Map, This_level);
    
    return Map;
}

void Generator::setting_events(Field& Map, Level& This_level){
    int Size_x = This_level.get_size_x();
    int Size_y = This_level.get_size_y();
    for(int i = 0; i < Size_y; i++){
        for(int j = 0; j < Size_x; j++){
            switch(This_level.get_symbol(j, i)){
                case static_cast<char>(Symbols::START):
                    Map.set_start(Point(j, i));
                    break;
                case static_cast<char>(Symbols::FINISH):
                    Map.set_destination(Point(j, i));
                    Map.get_cell(j, i).set_event(new Finish);
                    break;
                case static_cast<char>(Symbols::WALL):
                    Map.get_cell(j, i).set_passing(false);
                    break;
                case static_cast<char>(Symbols::SPIKE):
                    Map.get_cell(j, i).set_event(new SpikeDamage);
                    break;
                case static_cast<char>(Symbols::HEAL):
                    Map.get_cell(j, i).set_event(new Heal);
                    break;
            }
        }
    }
}

void Generator::setting_portals(Field& Map, Level& This_level){
    for(int n = 0; n < This_level.get_n_portals(); n++){
        Portal& Current_portal = This_level.get_portal(n);
        Point Entrance = Current_portal.get_entrance();
        Point Exit = Current_portal.get_exit();
        Map.get_cell(Entrance.get_x(), Entrance.get_y()).set_event(new Teleport(Exit));
    }
}