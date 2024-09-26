#include "Level.h"

bool Level::size_reader(std::ifstream& f){
    std::string tmp;
    std::getline(f, tmp);
    bool res;

    std::istringstream subtmp(tmp);
    std::string token;
    std::getline(subtmp, token, ' ');

    if(token != "Map_size:"){return false;}
    std::getline(subtmp, token, ' ');
    Size_x = std::atoi(token.c_str());
    std::getline(subtmp, token, ' ');
    Size_y = std::atoi(token.c_str());
    if(!Size_x || !Size_y){
        return false;
    }
    return true;
}

bool Level::ascii_map_reader(std::ifstream& f){
    std::string tmp;
    std::string token;
    
    ASCII_map = new char*[Size_y];
    for(int i = 0; i < Size_y; i++){
        ASCII_map[i] = new char[Size_x];
        std::getline(f, tmp);
        std::istringstream subtmp(tmp);
        for(int j = 0; j < Size_x; j++){
            if(!std::getline(subtmp, token, ' ') || token == "Portals:" || !token.size()){
                Size_y = i;
                return false;
            }
            ASCII_map[i][j] = *token.c_str();
        }
    }
    return true;
}

bool Level::portals_reader(std::ifstream& f){
    std::string tmp;
    std::string token;
    std::getline(f, tmp);
    std::istringstream subtmp(tmp);
    std::getline(subtmp, token, ' ');
    if(token != "Portals:"){return false;}

    std::getline(subtmp, token, ' ');
    n_portals = std::atoi(token.c_str());
    int x1, y1, x2, y2;
    for(int i = 0; i < n_portals; i++){
        if(!std::getline(f, tmp)){return false;}
        std::istringstream subtmp(tmp);
        std::getline(subtmp, token, '(');
        std::getline(subtmp, token, ';');
        if(!isalldigit(token)){return false;}
        x1 = std::atoi(token.c_str());
        std::getline(subtmp, token, ')');
        if(!isalldigit(token)){return false;}
        y1 = std::atoi(token.c_str());
        
        std::getline(subtmp, token, '(');
        std::getline(subtmp, token, ';');
        if(!isalldigit(token)){return false;}
        x2 = std::atoi(token.c_str());
        std::getline(subtmp, token, ')');
        if(!isalldigit(token)){return false;}
        y2 = std::atoi(token.c_str());
        Portals.push_back(Portal(Point(x1, y1), Point(x2, y2)));
    }
    if(std::getline(f, token)){return false;}
    return true;
}

Level::Level(std::string Path):is_initialised(false), ASCII_map(nullptr){
    std::ifstream f(std::string(std::filesystem::current_path()) + std::string("/../ProjectEchoes/Levels/") + Path);
    if(f.is_open()){
        if(!size_reader(f)){}
        else if(!ascii_map_reader(f)){}
        else if(!portals_reader(f)){}
        else{is_initialised = true;}
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

bool Level::isalldigit(std::string tmp){
    if(!tmp.size()){return false;}
    for(size_t i = 0; i < tmp.size(); i++){
        if(!std::isdigit(tmp[i])){return false;}
    }
    return true;
}

bool Level::is_read(){
    return is_initialised;
}