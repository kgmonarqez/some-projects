#include "LoggingManager.h"
#include "FileLogging.h"
#include "TerminalLogging.h"
#include "Logs/LooseLog.h"
#include "Logs/NewGameLog.h"
#include "Logs/UnidentifiedCommandLog.h"
#include "Logs/UsedCommandLog.h"
#include "Logs/WinLog.h"
#include "Logs/QuitLog.h"

LoggingManager::LoggingManager(Mechanics& Controller, Player& Entity, Field& Map, Input*& InputSystem){
    std::cout << "\x1B[2J\x1B[H";
    if(Terminal_logging_ask() | File_logging_ask()){
        Logs[LogNames::WIN] = new WinLog(Entity);
        Logs[LogNames::LOOSE] = new LooseLog(Controller);
        Logs[LogNames::NEW_GAME] = new NewGameLog(Controller, Map);
        Logs[LogNames::UNIDENTIFIED_COMMAND] = new UnidentifiedCommandLog(InputSystem);
        Logs[LogNames::USED_COMMAND] = new UsedCommandLog(InputSystem);
        Logs[LogNames::QUIT] = new QuitLog;
    }
}

LoggingManager::~LoggingManager(){
    if(Logs[LogNames::WIN]){delete Logs[LogNames::WIN];}
    if(Logs[LogNames::LOOSE]){delete Logs[LogNames::LOOSE];}
    if(Logs[LogNames::NEW_GAME]){delete Logs[LogNames::NEW_GAME];}
    if(Logs[LogNames::UNIDENTIFIED_COMMAND]){delete Logs[LogNames::UNIDENTIFIED_COMMAND];}
    if(Logs[LogNames::USED_COMMAND]){delete Logs[LogNames::USED_COMMAND];}
    if(Logs[LogNames::QUIT]){delete Logs[LogNames::QUIT];}
}

void LoggingManager::call_loggers(){
    for(auto*& Logger: Loggers_list){
        Logger->send_log(Called_logs);
    }
    Called_logs.clear();
}

void LoggingManager::add_log(LogNames LN){
    if(Logs[LN]){Logs[LN]->update();}
    Called_logs.push_back(Logs[LN]);
}

bool LoggingManager::Terminal_logging_ask(){
    std::string answer;
    std::cout << "Show logs in terminal?\n";
    while(answer != "No" && answer != "Yes"){
        std::getline(std::cin, answer);
    }
    if(answer == "Yes"){
        Loggers_list.push_back(new TerminalLogging);
        return true;
    }
    return false;
}

bool LoggingManager::File_logging_ask(){
    std::string answer;
    std::cout << "Need too state logs in file?\n";
    while(answer != "No" && answer != "Yes"){
        std::getline(std::cin, answer);
    }
    if(answer == "Yes"){
        std::cout << "Logs will be saved in file logs.txt\n";
        Loggers_list.push_back(new FileLogging("logs.txt"));
        return true;
    }
    return false;
}