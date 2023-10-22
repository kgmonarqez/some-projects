#include <iostream>
#include "Player/Player.h"
#include "Player/Mechanics.h"
#include "World/Cell.h"
#include "World/Field.h"
#include "Events/Event.h"
#include "Events/SpikeDamage.h"
#include "Events/Heal.h"
#include "Events/Teleport.h"
#include "World/Generator.h"

int main(){
    Player player = Player{"kgmonarchez"};
    Generator gen;
    Field Map = gen.level_generator(2);
    Mechanics Controller = Mechanics(player, Map);
    std::cout << player.get_hp() << '\n';
    return 0;
}