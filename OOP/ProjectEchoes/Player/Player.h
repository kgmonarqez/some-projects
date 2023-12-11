#pragma once
#include <iostream>

#define DEFAULT_SPEED 1
#define DEFAULT_MANA 100
#define DEFAULT_HP 100
#define DEFAULT_SCORES 0
#define DEFAULT_NAME std::string("Player")
#define DEFAULT_DAMAGE 20

class Player{
private:
    std::string Nickname;
    int HP;
    int Scores;
    int Mana;
    int Speed;
    int Damage;
public:
    Player(std::string New_Nickname=DEFAULT_NAME);

    int get_hp();
    int get_mana();
    int get_speed();
    int get_scores();
    int get_damage();
    std::string get_name();

    void set_name(std::string New_Nickname);
    void set_hp(int New_HP);
    void set_mana(int New_Mana);
    void set_speed(int New_Speed);
    void set_scores(int New_Scores);
    void set_damage(int New_Damage);

    bool check_hp();
    bool check_mana();
};