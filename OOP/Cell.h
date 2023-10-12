#pragma once

class Cell{
private:
    char Symbol;
    bool Passing;
public:
    Cell(bool Input_passing=true);

    void set_passing(bool Input_passing);
    void set_symbol(char Input_symbol);

    char get_symbol();
    bool get_passing();
    
    Cell* copy_cell();
};