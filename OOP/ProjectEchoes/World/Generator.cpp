#include "Generator.h"

Field Generator::level_generator(int Level_num){
    switch(Level_num){
        case 1:
            return level1_generation();
        case 2:
            return level2_generation();
    }   
}

Field Generator::level1_generation(){
    int Field_size_x = 6;
    int Field_size_y = 5;
    char ASCII_map[Field_size_y][Field_size_x] = {
    "F.....",
    "######",
    "0.HHH.",
    "#####.",
    "S.xxx."
    };
    Point Portal_destination = Point(5, 0);
    Field Map = Field(Field_size_x, Field_size_y);
    for(int i = 0; i < Field_size_y; i++){
        for(int j = 0; j < Field_size_x; j++){
            switch(ASCII_map[i][j]){
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
                case static_cast<char>(Symbols::PORTAL):
                    Map.get_cell(j, i).set_event(new Teleport(Portal_destination));
                    break;
            }
        }
    }
    return Map;
}

Field Generator::level2_generation(){
    int Field_size_x = 12;
    int Field_size_y = 13;
    char ASCII_map[Field_size_y][Field_size_x] = {
    "############",
    "#....#.....#",
    "#.##.#.#####",
    "#..#.#.#...#",
    "##.#.#...#.#",
    "S..#.#...#.#",
    "####.##..#.#",
    "#....#...#.#",
    "#.####.###.#",
    "#.#....#...#",
    "#.####.#...#",
    "#......#.#.#",
    "########F###"
    };
    Field Map = Field(Field_size_x, Field_size_y);
    for(int i = 0; i < Field_size_y; i++){
        for(int j = 0; j < Field_size_x; j++){
            std::cout << ASCII_map[i][j] << ' ';
            switch(ASCII_map[i][j]){
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
        std::cout << '\n';
    }
    return Map;
}