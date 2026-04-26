#include "shop.hpp"
#include <raylib.h>


Shop::Shop(GameState& gameState)
    : State(gameState) 
    {}

void Shop::draw(){
    DrawText("Press ENTER to go back", GetScreenWidth() - MeasureText("Press ENTER to go back", 23) - 23, GetScreenHeight() - 40, 23, GOLD);
}
void Shop::update(){
    if (IsKeyPressed(KEY_ENTER)){
        gameState        = MENU;                // return  to menu effectively
    }
}