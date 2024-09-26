#include "Player.h"

Player::Player(std::string New_Nickname){
    set_name(New_Nickname);
    set_hp(DEFAULT_HP);
    set_scores(DEFAULT_SCORES);
    set_mana(DEFAULT_MANA);
    set_speed(DEFAULT_SPEED);
    set_damage(DEFAULT_DAMAGE);
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

int Player::get_damage(){
    return Damage;
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

void Player::set_damage(int New_Damage){
    Damage = New_Damage;
}

bool Player::check_hp(){
    return HP > 0 && HP <= DEFAULT_HP;
}

bool Player::check_mana(){
    return Mana > 0 && Mana <= DEFAULT_MANA;
}