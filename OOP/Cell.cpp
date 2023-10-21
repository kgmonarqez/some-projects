#include "Cell.h"

Cell::Cell(bool Input_passing){
    set_passing(Input_passing);
}

void Cell::set_passing(bool Input_passing){
    Passing = Input_passing;
}

bool Cell::get_passing(){
    return Passing;
}

Cell* Cell::copy_cell(){
    return new Cell(this->Passing);
}