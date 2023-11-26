#include "SpikeDamage.h"

bool SpikeDamage::action(Mechanics& Controller){
    Controller.damage_receiving(SPIKE_DAMAGE);
    return false;
}

SpikeDamage* SpikeDamage::copy(){
    return new SpikeDamage(*this);
}

char SpikeDamage::get_representation(){
    return 'x';
}