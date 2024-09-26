#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>
#include <vector>
#include <cctype>
#include "Portal.h"

class Level{
private:
    char** ASCII_map;
    int Size_x;
    int Size_y;
    int n_portals;
    std::vector<Portal> Portals;

    bool is_initialised;

    bool size_reader(std::ifstream& f);
    bool ascii_map_reader(std::ifstream& p);
    bool portals_reader(std::ifstream& p);

    bool isalldigit(std::string tmp);
public:
    Level(std::string Path);
    ~Level();
    
    int get_size_x();
    int get_size_y();
    char get_symbol(int x, int y);
    int get_n_portals();
    Portal& get_portal(int n);

    bool is_read();
};