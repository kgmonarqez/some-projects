#include "Cell.h"

Cell::Cell(bool Input_passing, Event* Input_event){
    set_passing(Input_passing);
    set_event(Input_event);
}

void Cell::set_passing(bool Input_passing){
    Passing = Input_passing;
}

void Cell::set_event(Event* Input_event){
    Current_event = Input_event;
}

bool Cell::get_passing(){
    return Passing;
}

Event* Cell::get_event(){
    return Current_event;
}