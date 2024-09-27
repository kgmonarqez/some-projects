#include "Level.h"

void Level::size_reader(std::ifstream& f){
    std::string tmp;
    std::getline(f, tmp);

    std::istringstream subtmp(tmp);
    std::string token;
    std::getline(subtmp, token, ' ');
    
    std::getline(subtmp, token, ' ');
    Size_x = std::atoi(token.c_str());

    std::getline(subtmp, token, ' ');
    Size_y = std::atoi(token.c_str());
}

void Level::ascii_map_reader(std::ifstream& f){
    std::string tmp;
    std::string token;
    
    ASCII_map = new char*[Size_y];
    for(int i = 0; i < Size_y; i++){
        ASCII_map[i] = new char[Size_x];
        std::getline(f, tmp);
        std::istringstream subtmp(tmp);
        for(int j = 0; j < Size_x; j++){
            std::getline(subtmp, token, ' ');
            ASCII_map[i][j] = *token.c_str();
        }
    }
}

void Level::portals_reader(std::ifstream& f){
    std::string tmp;
    std::string token;
    std::getline(f, tmp);
    std::istringstream subtmp(tmp);
    std::getline(subtmp, token, ' ');

    std::getline(subtmp, token, ' ');
    n_portals = std::atoi(token.c_str());
    int x1, y1, x2, y2;
    for(int i = 0; i < n_portals; i++){
        std::getline(f, tmp);
        std::istringstream subtmp(tmp);
        std::getline(subtmp, token, '(');
        std::getline(subtmp, token, ';');
        x1 = std::atoi(token.c_str());
        std::getline(subtmp, token, ')');
        y1 = std::atoi(token.c_str());

        std::getline(subtmp, token, '(');
        std::getline(subtmp, token, ';');
        x2 = std::atoi(token.c_str());
        std::getline(subtmp, token, ')');
        y2 = std::atoi(token.c_str());
        Portals.push_back(Portal(Point(x1, y1), Point(x2, y2)));
    }
}

Level::Level(std::string Path){
    std::ifstream f(std::string(std::filesystem::current_path()) + std::string("/../ProjectEchoes/Levels/") + Path);
    if(f.is_open()){
        size_reader(f);
        ascii_map_reader(f);
        portals_reader(f);
        f.close();
    }
}

Level::~Level(){
    if(ASCII_map){
        for(int i = 0; i < Size_y; i++){
            if(ASCII_map[i]){
                delete[] ASCII_map[i];
            }
        }
        delete[] ASCII_map;
    }
}

int Level::get_size_x(){
    return Size_x;
}

int Level::get_size_y(){
    return Size_y;
}

char Level::get_symbol(int x, int y){
    return ASCII_map[y][x];
}

Portal& Level::get_portal(int n){
    return Portals[n];
}

int Level::get_n_portals(){
    return n_portals;
}
