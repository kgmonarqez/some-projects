#pragma once
#include "Log.h"
#include "../../Input/Input.h"

class UnidentifiedCommandLog: public Log{
private:
    Input*& ObservedInputSystem;

    unsigned int Key;
public:
    UnidentifiedCommandLog(Input*& InputSystem);
    unsigned int get_key() const;
    void update();
};