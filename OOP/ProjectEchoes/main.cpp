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
#include "World/Level.h"

int main(){
    Generator gen;
    Field Map = gen.level_select(1);
    return 0;
}