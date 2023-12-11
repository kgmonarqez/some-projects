#pragma once
#include "Logging.h"

class TerminalLogging: public Logging{
public:
    void send_log(std::list<Log*> Called_logs);
};