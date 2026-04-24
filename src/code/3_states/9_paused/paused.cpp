#include <raylib.h>
#include "paused.hpp"


Paused::Paused(GameState& gameState, Playing& playing)
: State(gameState), playing(playing)
{
    gameResumedSFX = LoadSound("src/assets/sounds/sfx/gameResumed.mp3");
    gameStoppedSFX = LoadSound("src/assets/sounds/sfx/gameStopped.mp3");
}
Paused::~Paused(){
    UnloadSound(gameResumedSFX);
    UnloadSound(gameStoppedSFX);
}

void Paused::draw(){
    int cx = GetScreenWidth()  / 2;
    int cy = GetScreenHeight() / 2;

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.23f));         // a translucent black overlay 

    DrawText("PAUSED",
                cx - MeasureText("PAUSED", textSize) / 2,
                cy - textSize - 40, textSize, GOLD);

    DrawText(TextFormat("Score:  %06d", playing.getScore()),   cx - 130, cy - 5,  26, RAYWHITE);
    DrawText(TextFormat("Wave:   %02d", playing.getWaveNum()), cx - 130, cy + 30, 26, RAYWHITE);

    DrawLineEx({30, (float)(cy + 83)}, {(float)(GetScreenWidth() - 30), (float)(cy + 83)}, 1, DARKGRAY);

    DrawText("P  -  Resume",       cx - MeasureText("P  -  Resume",       26) / 2, cy + 133, 26, GREEN);
    DrawText("M  -  Quit to Menu", cx - MeasureText("M  -  Quit to Menu", 26) / 2, cy + 163, 26, RED);
}
void Paused::update(){
    if (IsKeyPressed(KEY_P)){
        PlaySound(gameResumedSFX);

        gameState = PLAYING;
    }

    if (IsKeyPressed(KEY_M)){
        PlaySound(gameStoppedSFX);
        playing.reset();

        gameState = MENU;
    }
}