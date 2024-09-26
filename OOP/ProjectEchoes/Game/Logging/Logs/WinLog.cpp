#include "WinLog.h"

WinLog::WinLog(Player& Entity):ObservedPlayer(Entity){
    update();
}

std::map<StatsNames, int> WinLog::get_stats() const{
    return Stats;
}

void WinLog::update(){
    Stats[StatsNames::HP] = ObservedPlayer.get_hp();
    Stats[StatsNames::SCORES] = ObservedPlayer.get_scores();
    Stats[StatsNames::MANA] = ObservedPlayer.get_mana();
    Stats[StatsNames::SPEED] = ObservedPlayer.get_speed();
    Stats[StatsNames::DAMAGE] = ObservedPlayer.get_damage();
}