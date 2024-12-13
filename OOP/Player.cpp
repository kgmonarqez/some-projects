#include "Player.h"

Player::Player(std::string New_Nickname=DEFAULT_NAME){
    set_name(New_Nickname);
    set_hp(DEFAULT_HP);
    set_scores(DEFAULT_SCORES);
    set_mana(DEFAULT_MANA);
    set_speed(DEFAULT_SPEED);
}

int Player::get_hp(){
    return HP;
}

int Player::get_mana(){
    return Mana;
}

int Player::get_speed(){
    return Speed;
}

int Player::get_scores(){
    return Scores;
}

std::string Player::get_name(){
    return Nickname;    
}

void Player::set_name(std::string New_Nickname){
    Nickname = New_Nickname;
}

void Player::set_hp(int New_HP){
    HP = New_HP;
}

void Player::set_mana(int New_Mana){
    Mana = New_Mana;
}

void Player::set_speed(int New_Speed){
    Speed = New_Speed;
}

void Player::set_scores(int New_Scores){
    Scores = New_Scores;
}

bool Player::check_hp(){
    return HP > 0 && HP <= DEFAULT_HP;
}

bool Player::check_mana(){
    return Mana > 0 && Mana <= DEFAULT_MANA;
}