#include "TerminalLogging.h"
#include "OstreamOverload.h"
#include <iostream>

void TerminalLogging::send_log(std::list<Log*> Called_logs){
    for(auto*& L: Called_logs){
        std::cout << L;
    }
}