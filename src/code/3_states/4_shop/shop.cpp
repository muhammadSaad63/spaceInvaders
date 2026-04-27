#include "shop.hpp"


Shop::Shop(GameState& gameState)
    : State(gameState) 
    , memePlayed(false)
    {
        shopWowSFX = LoadSound("src/assets/sounds/sfx/shopWow.mp3");
        wowSoEmpty = LoadTexture("src/assets/graphics/ui/misc/wowSoEmpty.jpg");
        // wowSoEmpty = LoadTexture("src/assets/graphics/ui/misc/wowSoEmptyT.png");
    }
Shop::~Shop(){
    UnloadSound(shopWowSFX);
    UnloadTexture(wowSoEmpty);
}

void Shop::draw(){
    DrawTexture(wowSoEmpty, (GetScreenWidth()/2 - wowSoEmpty.width/2), (GetScreenHeight()/2 - wowSoEmpty.height/2), WHITE);
    DrawText("Press ENTER to go back", (GetScreenWidth() - MeasureText("Press ENTER to go back", 23) - 23), (GetScreenHeight() - 40), 23, GOLD);
}
void Shop::update(){
    if (!memePlayed){
        PlaySound(shopWowSFX);
        memePlayed = true;

        return;
    }

    if (IsKeyPressed(KEY_ENTER)){
        memePlayed = false;
        gameState  = MENU;                         // return  to menu effectively
    }
}