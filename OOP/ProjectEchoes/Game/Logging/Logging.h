#pragma once
#include "Logs/Log.h"
#include <list>

class Logging{
public:
    virtual void send_log(std::list<Log*> Called_logs) = 0;
};