#include "Heal.h"

void Heal::action(Mechanics& Controller){
    Controller.healing(HEAL_POINTS);
}