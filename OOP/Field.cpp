#include "Field.h"
#include <algorithm>
#include <iostream>
Field::Field(int Input_field_size_x, int Input_field_size_y){
    if(Input_field_size_x >= MIN_FIELD_SIZE_X && Input_field_size_y >= MIN_FIELD_SIZE_Y){
        Field_size_x = Input_field_size_x;
        Field_size_y = Input_field_size_y;
        Map = new Cell*[Field_size_y];
        for(int i = 0; i < Field_size_y; i++){
            Map[i] = new Cell[Field_size_x];
            for(int j = 0; j < Field_size_x; j++){
                Map[i][j] = Cell{};
            }
        }
    }
}

Field::Field(const Field& Copy):Start(Copy.Start), Destination(Copy.Destination), Field_size_x(Copy.Field_size_x), Field_size_y(Copy.Field_size_y){
    Map = new Cell*[Field_size_y];
    for(int i = 0; i < Field_size_y; i++){
        Map[i] = new Cell[Field_size_x];
    }
    std::copy(&Copy.Map[0][0], &Copy.Map[0][0]+Field_size_x*Field_size_y, &Map[0][0]);
}

Field& Field::operator=(const Field& Copy){
    this->~Field();
    *this = Field(Copy);
    return *this;
}

Field::Field(Field&& Move){
    Map = std::exchange(Move.Map, nullptr);
    std::swap(Field_size_x, Move.Field_size_x);
    std::swap(Field_size_y, Move.Field_size_y);
    std::swap(Start, Move.Start);
    std::swap(Destination, Move.Destination);
}

Field& Field::operator=(Field&& Move){
    if(this != &Move && Move.Map){
        this->~Field();
        Field(std::move(Move));
    }
    return *this;
}

Field::~Field(){
    if(Map){
        for(int i = 0; i < Field_size_y; i++){
            delete[] Map[i];
        }
        delete[] Map;
        Map = nullptr;
    }
}

int Field::get_field_size_x(){
    return Field_size_x;
}

int Field::get_field_size_y(){
    return Field_size_y;
}

Cell& Field::get_cell(int x, int y){
    return Map[y][x];
}

bool Field::check_passing(int x, int y){
    return Map[y][x].get_passing();
}