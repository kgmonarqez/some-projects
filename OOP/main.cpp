#include <iostream>
#include "Player.h"
#include "Mechanics.h"
#include "Cell.h"
#include "Field.h"

int main(){
    Player player{"kgmonarchez"};
    Field map = Field(10, 10);
    Field copy = Field(std::move(map));
    copy = std::move(map);
    return 0;
}