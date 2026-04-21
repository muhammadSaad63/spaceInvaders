#include "paused.hpp"


Paused::Paused(GameState& gameState, Playing& playing) 
: State(gameState)
, playing(playing) 
{
    gameResumedSFX  = LoadSound("src/assets/sounds/sfx/active/gameResumed.mp3");
    gameStoppedSFX  = LoadSound("src/assets/sounds/sfx/active/gameStopped.mp3");
}
Paused::~Paused(){
    UnloadSound(gameResumedSFX);
    UnloadSound(gameStoppedSFX);
}

void Paused::draw(){
    // DrawText("GamePlay Paused.\n- Press \"p\" to resume.\n- Press \"x\" to finish.", GetScreenWidth() / 2 - MeasureText("GamePlay Paused.\n- Press \"p\" to resume.\n- Press \"x\" to finish.", textSize) / 2, GetScreenHeight() /2 - 3*textSize/2, textSize, GOLD);        // thats long....;  100 here is the fontsize
    DrawText("GamePlay Paused.", GetScreenWidth() / 2 - MeasureText("GamePlay Paused.", textSize) / 2, GetScreenHeight()/2 - textSize/2 - 50, textSize, GOLD);        // thats long....;  100 here is the fontsize
    DrawText("- Press \"p\" to resume.\n- Press \"x\" to finish.", GetScreenWidth() / 2 - MeasureText("- Press \"p\" to resume.\n- Press \"x\" to finish.", textSize/1.5) / 2, GetScreenHeight()/2 - textSize/2 - 50 + textSize + 30, textSize/1.5, GOLD);
}
void Paused::update(){
    if (IsKeyPressed(KEY_P)){
        PlaySound(gameResumedSFX);

        gameState = PLAYING;
    }

    if (IsKeyPressed(KEY_X)){
        PlaySound(gameStoppedSFX);

        gameState = MENU;
        // playing.resetAll();
    }
}
