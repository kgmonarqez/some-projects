#pragma once
#include "../World/Generator.h"
#include "../World/Field.h"
#include "Input/TerminalInput.h"
#include "ControlSchemes/KeyboardControl.h"
#include "InputModelSetter.h"
#include "Rendering/RenderingWatcher.h"

#define LAST_LEVEL_NUM 2

class Launcher{
private:
    Input* InputModel;
    RenderingWatcher RW;

    bool ask_for_replay();
public:
    Launcher();
    void run();
};