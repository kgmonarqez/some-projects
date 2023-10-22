#include "SpikeDamage.h"

void SpikeDamage::action(Mechanics& Controller){
    Controller.damage_receiving(SPIKE_DAMAGE);
}