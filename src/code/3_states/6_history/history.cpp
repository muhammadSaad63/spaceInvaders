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
    // column headers
    DrawText("#",        posX,          posY, textSize, DARKGRAY);
    DrawText("Score",    posX + 60,     posY, textSize, DARKGRAY);
    DrawText("Wave",     posX + 220,    posY, textSize, DARKGRAY);
    DrawText("Kills",    posX + 340,    posY, textSize, DARKGRAY);
    DrawText("Time",     posX + 460,    posY, textSize, DARKGRAY);
    posY += textSize + 5;

    // seperator line
    DrawLineEx({(float)posX, (float)posY}, {(float)GetScreenWidth() - posX, (float)posY}, 1, DARKGRAY);
    posY += 10;

    // printing history
    for (auto entryNum {0}; entryNum < history.size(); ++entryNum){
        auto& entry = history[entryNum];

        // rank color — gold, silver, bronze, then plain white
        Color rankColor = (entryNum == 0)? GOLD
                        : (entryNum == 1)? LIGHTGRAY
                        : (entryNum == 2)? Color{205, 127, 50, 255}              // bronze
                        :                  RAYWHITE;

        DrawText(TextFormat("%d",      entryNum + 1),                                               posX,       posY, textSize, rankColor);
        DrawText(TextFormat("%05d",    entry.score),                                                posX + 60,  posY, textSize, YELLOW);
        DrawText(TextFormat("%d",      entry.waveReached),                                          posX + 220, posY, textSize, SKYBLUE);
        DrawText(TextFormat("%d",      entry.enemiesDefeated),                                      posX + 340, posY, textSize, RED);
        DrawText(TextFormat("%dm %ds", ((int)entry.timePlayed / 60), ((int)entry.timePlayed % 60)), posX + 460, posY, textSize, LIME);

        posY += textSize + 15;
    }
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
        : State(gameState)
        , dataBase(dataBase)
        , historyLoaded(false)
        , maxEntriesToFetch(10)
        {
            stateChangedSFX = LoadSound("assets/sounds/sfx/stateChanged.mp3");
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
    if (!historyLoaded || history.empty())
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
