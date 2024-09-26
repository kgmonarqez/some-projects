#pragma once
#include "Logging.h"
#include "../../Player/Mechanics.h"
#include "../Input/Input.h"
#include <list>
#include <map>
#include <iostream>

enum class LogNames{WIN, LOOSE, USED_COMMAND, UNIDENTIFIED_COMMAND, NEW_GAME, QUIT};

class LoggingManager{
private:
    std::list<Logging*> Loggers_list;
    std::map<LogNames, Log*> Logs;
    std::list<Log*> Called_logs;

    bool Terminal_logging_ask();
    bool File_logging_ask();
public:
    LoggingManager(Mechanics& Controller, Player& Entity, Field& Map, Input*& InputSystem);
    ~LoggingManager();
    void call_loggers();
    void add_log(LogNames LN);
};