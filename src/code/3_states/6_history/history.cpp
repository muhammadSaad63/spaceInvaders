#include <raylib.h>
#include "history.hpp"


// helpers
void History::drawHeader(int& posY){
    DrawText("History", posX, posY, textSize + 10, GOLD);
    posY += (textSize + 10) + 15;

    DrawLineEx({(float)posX, (float)posY}, {(float)GetScreenWidth() - posX, (float)posY}, 1, DARKGRAY);
    posY += 30;
}
void History::drawHistory(int& posY){
    //
}
void History::drawOverLay(){
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.5f));
        DrawText("No games played yet  :(",
                    GetScreenWidth()/2  - MeasureText("No games played yet  :(", 40)/2,
                    GetScreenHeight()/2 - 20, 40, DARKGRAY);
}

void History::loadHistory(){
    if (!historyLoaded){
        historyLoaded = true;
        history       = dataBase.getHistory(maxEntriesToFetch);
    }
}

History::History(GameState& gameState, DataBase& dataBase)
        : State(gameState), dataBase(dataBase)
        {
            stateChangedSFX = LoadSound("src/assets/sounds/sfx/stateChanged.mp3");
        }
History::~History(){
    UnloadSound(stateChangedSFX);
}

void History::draw(){
    int posY = initPosY;  

    // header
    drawHeader(posY);

    // table
    drawHistory(posY);

    // exit hint matches settings style
    DrawText("Press ENTER to go back", GetScreenWidth() - MeasureText("Press ENTER to go back", textSize) - 23, GetScreenHeight() - 40, textSize, GOLD);

    // making a dark black rectangular overlay over screen if no stats there
    if (!historyLoaded || !history.empty())
        drawOverLay();
}
void History::update(){
    loadHistory();

    // exiting from history state
    if (IsKeyPressed(KEY_ENTER)){
        historyLoaded    = false;               // so that history will be reloaded when state again entered
        PlaySound(stateChangedSFX);

        gameState        = MENU;                // return  to menu effectively
    }
}
