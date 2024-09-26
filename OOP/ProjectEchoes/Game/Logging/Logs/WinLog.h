#pragma once
#include "Log.h"
#include <map>
#include "../../../Player/Player.h"

enum class StatsNames{HP, SCORES, MANA, SPEED, DAMAGE};

class WinLog: public Log{
private:
    Player& ObservedPlayer;

    std::map<StatsNames, int> Stats;
public:
    WinLog(Player& Entity);
    std::map<StatsNames, int> get_stats() const;
    void update();
};