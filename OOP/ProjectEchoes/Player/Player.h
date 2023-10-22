#pragma once
#include <iostream>

#define DEFAULT_SPEED 1
#define DEFAULT_MANA 100
#define DEFAULT_HP 100
#define DEFAULT_SCORES 0
#define DEFAULT_NAME "Player"

class Player{
private:
    std::string Nickname;
    int HP;
    int Scores;
    int Mana;
    int Speed;

public:
    Player(std::string New_Nickname);

    int get_hp();
    int get_mana();
    int get_speed();
    int get_scores();
    std::string get_name();

    void set_name(std::string New_Nickname);
    void set_hp(int New_HP);
    void set_mana(int New_Mana);
    void set_speed(int New_Speed);
    void set_scores(int New_Scores);

    bool check_hp();
    bool check_mana();
};