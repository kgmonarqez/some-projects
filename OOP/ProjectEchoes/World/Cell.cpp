#include "Cell.h"

Cell::Cell(bool Input_passing, Event* Input_event):Passing(Input_passing), Current_event(Input_event){}

Cell::Cell(const Cell& Copy):Passing(Copy.Passing), Current_event(nullptr){
    if(Copy.Current_event){
        Current_event = Copy.Current_event->copy();
    }
}

Cell::Cell(Cell&& Move):Passing(true), Current_event(nullptr){
    Current_event = std::exchange(Move.Current_event, nullptr);
}

Cell::~Cell(){
    if(Current_event){
        delete Current_event;
    }
}

Cell& Cell::operator=(const Cell& Copy){
    Cell Temp(Copy);
    set_event();
    std::swap(Current_event, Temp.Current_event);
    std::swap(Passing, Temp.Passing);
    return *this;
}

Cell& Cell::operator=(Cell&& Move){
    if(this != &Move){
        set_event();
        std::swap(Passing, Move.Passing);
        Current_event = std::exchange(Move.Current_event, nullptr);
    }
    return *this;
}

void Cell::set_passing(bool Input_passing){
    Passing = Input_passing;
}

void Cell::set_event(Event* Input_event){
    if(Current_event){
        delete Current_event;
    }
    Current_event = Input_event;
}

bool Cell::get_passing(){
    return Passing;
}

Event* Cell::get_event(){
    return Current_event;
}