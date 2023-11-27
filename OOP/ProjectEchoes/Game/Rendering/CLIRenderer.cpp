#include "CLIRenderer.h"

void CLIRenderer::render(Field& Map, Player& Entity, Point Position){
    std::cout << "\x1B[2J\x1B[H";
    if(Entity.check_hp()){
        for(int y = 0; y < Map.get_field_size_y(); y++){
            for(int x = 0; x < Map.get_field_size_x(); x++){
                char symb;
                if(Position == Point(x, y)){
                    std::cout << '@' << ' ';
                }
                else{
                    std::cout << define_event(Map.get_cell(x, y)) << ' ';
                }
            }
            std::cout << '\n';
        }
        std::cout << "HP: " << Entity.get_hp() << '\n'; 
        std::cout << "Position: " << '(' << Position.get_x() << ';' << Position.get_y() << ")\n";
    }
    else{
        std::cout << "Continue?\n[Y/Yes, N/No]: ";
    }
}

char CLIRenderer::define_event(Cell& Current_cell){
    if(Current_cell.get_event()){return Current_cell.get_event()->get_representation();}
    else if(!Current_cell.get_passing()){return '#';}
    return '.';
    /*if(dynamic_cast<Heal*>(Current_event)){
        return 'H';
    }
    else if(dynamic_cast<SpikeDamage*>(Current_event)){
        return 'x';
    }
    else if(dynamic_cast<Teleport*>(Current_event)){
        return '0';
    }
    else if(!Current_cell.get_passing()){
        return '#';
    }*/
}