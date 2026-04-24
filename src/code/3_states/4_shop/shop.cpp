#include "shop.hpp"
#include <raylib.h>


Shop::Shop(GameState& gameState)
    : State(gameState) 
    {}

void Shop::draw(){
    //
}
void Shop::update(){
    if (IsKeyPressed(KEY_ENTER)){
        gameState        = MENU;                // return  to menu effectively
    }
}