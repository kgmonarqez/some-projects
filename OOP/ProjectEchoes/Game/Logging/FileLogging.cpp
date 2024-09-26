#include "FileLogging.h"
#include "OstreamOverload.h"

FileLogging::FileLogging(std::string File_name){
    path = std::string(std::filesystem::current_path()) + std::string("/../ProjectEchoes/Game/Logging/") + File_name;
    std::ifstream f(path);
    if(!f.is_open()){
        std::cout << "Wrong file name\n";
    }
    f.close();
}

void FileLogging::send_log(std::list<Log*> Called_logs){
    std::fstream f(path, std::fstream::app);
    if(f.is_open()){
        for(auto*& L: Called_logs){
            f << L;
        }
    }
    f.close();
}