#include "Cell.h"

Cell::Cell(bool Input_passing){
    set_passing(Input_passing);
}

void Cell::set_passing(bool Input_passing){
    Passing = Input_passing;
}

void Cell::set_symbol(char Input_symbol){
    Symbol = Input_symbol;
}

char Cell::get_symbol(){
    return Symbol;
}

bool Cell::get_passing(){
    return Passing;
}

Cell* Cell::copy_cell(){
    Cell *copy = new Cell;
    copy->set_symbol(this->Symbol);
    copy->set_passing(this->Passing);
    return copy;
}