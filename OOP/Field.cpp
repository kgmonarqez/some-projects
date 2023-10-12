#include "Field.h"

Field::Field(int Input_field_size_x, int Input_field_size_y){
    if(Input_field_size_x >= MIN_FIELD_SIZE_X and Input_field_size_y >= MIN_FIELD_SIZE_Y){
        Field_size_x = Input_field_size_x;
        Field_size_y = Input_field_size_y;
        Map = new Cell**[Field_size_x];
        for(int i = 0; i < Field_size_x; i++){
            Map[i] = new Cell*[Field_size_y];
            for(int j = 0; j < Field_size_y; j++){
                Map[i][j] = new Cell;
            }
        }
    }
}

Field::~Field(){
    for(int i = 0; i < Field_size_x; i++){
        for(int j = 0; j < Field_size_y; j++){
            delete Map[i][j];
        }
        delete[] Map[i];
    }
    delete[] Map;
}

int Field::get_field_size_x(){
    return Field_size_x;
}

int Field::get_field_size_y(){
    return Field_size_y;
}

bool Field::check_passing(int x, int y){
    return Map[x][y]->get_passing();
}