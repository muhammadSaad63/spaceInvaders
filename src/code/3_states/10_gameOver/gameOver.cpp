#include <string>
#include "gameOver.hpp"
using std::string;

GameOver::GameOver(GameState& gameState, DataBase& dataBase, Playing& playing) 
        : State(gameState)
        , dataBase(dataBase)
        , playing(playing)
        , timer(0)
        , gameSaved(false)
        {
            stateChangedSFX = LoadSound("src/assets/sounds/sfx/stateChanged.mp3");
        }
GameOver::~GameOver(){
    UnloadSound(stateChangedSFX);
}

void GameOver::draw(){
    int cx = GetScreenWidth()  / 2;
    int cy = GetScreenHeight() / 2;

    string title = "GAME  OVER";
    DrawText(title.c_str(), cx - MeasureText(title.c_str(), 80)/2, cy - 120, 80, RED);

    DrawText(TextFormat("Score:           %06d",   playing.getScore()),           cx - 180, cy - 10, 26, GOLD);
    DrawText(TextFormat("Wave Reached:      %02d", playing.getWaveNum()),         cx - 180, cy + 30, 26, SKYBLUE);
    DrawText(TextFormat("Enemies Killed:    %04d", playing.getEnemiesDefeated()), cx - 180, cy + 70, 26, LIME);

    if (timer > 1.5f){
        DrawText("R  -  Play Again", cx - MeasureText("R  -  Play Again", 26)/2, cy + 230, 26, GREEN);
        DrawText("M  -  Main Menu",  cx - MeasureText("M  -  Main Menu",  26)/2, cy + 265, 26, RAYWHITE);
    }
}

void GameOver::update(){
    if (!gameSaved){
        GameData gameData = GameData{-1, playing.getScore(), playing.getEnemiesDefeated(), playing.getWaveNum(), playing.getTimePlayed()};
        dataBase.addGame(gameData);

        gameSaved = true;
    }

    timer += GetFrameTime();
    if (timer < 1.5f) return;

    if (IsKeyPressed(KEY_R)){ 
        timer = 0; 
        playing.reset(); 
        gameSaved = false;

        gameState = PLAYING; 
    }

    if (IsKeyPressed(KEY_M)){ 
        timer = 0; 
        playing.reset(); 
        PlaySound(stateChangedSFX);
        gameSaved = false;

        gameState = MENU;    
    }
}