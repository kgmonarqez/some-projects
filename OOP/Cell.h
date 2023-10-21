#pragma once

class Cell{
private:
    bool Passing;
public:
    Cell(bool Input_passing=true);

    void set_passing(bool Input_passing);

    bool get_passing();
    
    Cell* copy_cell();
};