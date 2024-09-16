#pragma once
#include "../World/Generator.h"
#include "../World/Field.h"
#include "KeyboardInput.h"

#define LAST_LEVEL_NUM 2

class Launcher{
private:
    KeyboardInput KI;

    bool ask_for_replay();
public:
    Launcher();
};