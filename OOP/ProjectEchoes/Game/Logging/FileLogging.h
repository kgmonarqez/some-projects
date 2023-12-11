#pragma once
#include "Logging.h"
#include <fstream>
#include <filesystem>
#include <iostream>

class FileLogging: public Logging{
private:
    std::string path;
public:
    FileLogging(std::string File_name);
    void send_log(std::list<Log*> Called_logs);
};