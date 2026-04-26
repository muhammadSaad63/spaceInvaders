#include <raylib.h>
#include "statistics.hpp"


void Statistics::drawHeader(int& posY){
    DrawText("Statistics", posX, posY, textSize + 10, GOLD);
    posY += (textSize + 10) + 15;

    DrawLineEx({(float)posX, (float)posY}, {(float)GetScreenWidth() - posX, (float)posY}, 1, DARKGRAY);
    posY += 30;
}
void Statistics::drawScore(int& posY){
    DrawText("Score",                               posX, posY, textSize, GOLD);
    posY += textSize + 5;

    DrawText("Total Score",                           posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.totalScore),      posX + offset, posY, textSize, YELLOW);
    posY += textSize + 5;

    DrawText("Best Score",                            posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.maxScorePerGame), posX + offset, posY, textSize, YELLOW);
    posY += textSize + 5;

    DrawText("Avg Score / Game",                      posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.avgScorePerGame), posX + offset, posY, textSize, YELLOW);
    posY += textSize + 23;
}
void Statistics::drawEnemiesDefeated(int& posY){
    DrawText("Enemies",                                    posX, posY, textSize, GOLD);
    posY += textSize + 5;
    
    DrawText("Total Defeated",                             posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.totalEnemiesDefeated), posX + offset, posY, textSize, RED);
    posY += textSize + 5;
    
    DrawText("Most In One Game",                           posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.maxEnemiesDefeatedPerGame), posX + offset, posY, textSize, RED);
    posY += textSize + 5;
    
    DrawText("Avg Defeated / Game",                        posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.avgEnemiesDefeatedPerGame), posX + offset, posY, textSize, RED);
    posY += textSize + 23;
}
void Statistics::drawWavesReached(int& posY){
    DrawText("Waves",                                      posX, posY, textSize, GOLD);
    posY += textSize + 5;
    
    DrawText("Total Waves Cleared",                        posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.totalWavesCleared),    posX + offset, posY, textSize, SKYBLUE);
    posY += textSize + 5;

    DrawText("Best Wave Reached",                          posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.maxWavesClearedPerGame), posX + offset, posY, textSize, SKYBLUE);
    posY += textSize + 5;
    
    DrawText("Avg Wave / Game",                            posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.avgWavesClearedPerGame), posX + offset, posY, textSize, SKYBLUE);
    posY += textSize + 23;
}
void Statistics::drawTimePlayed(int& posY){
    DrawText("Time",                                       posX, posY, textSize, GOLD);
    posY += textSize + 5;

    DrawText("Total Time Played",                          posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%dm %ds", ((int)stats.totalTimePlayed / 60),      ((int)stats.totalTimePlayed % 60)),      posX + offset, posY, textSize, LIME);
    posY += textSize + 5;

    DrawText("Longest Game",                               posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%dm %ds", ((int)stats.maxTimePlayedPerGame / 60), ((int)stats.maxTimePlayedPerGame % 60)), posX + offset, posY, textSize, LIME);
    posY += textSize + 5;

    DrawText("Avg Time / Game",                            posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%dm %ds", ((int)stats.avgTimePlayedPerGame / 60), ((int)stats.avgTimePlayedPerGame % 60)), posX + offset, posY, textSize, LIME);
    posY += textSize + 25;

    DrawLineEx({(float)posX, (float)posY}, {(float)GetScreenWidth() - posX, (float)posY}, 1, DARKGRAY);
    posY += 15;
}
void Statistics::drawOverLay(){
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.5f));
        DrawText("No games played yet  :(",
                    GetScreenWidth()/2  - MeasureText("No games played yet  :(", 40)/2,
                    GetScreenHeight()/2 - 20, 40, DARKGRAY);
}

void Statistics::loadStats(){
    if (!statsLoaded){
        stats       = dataBase.getStatistics();
        statsLoaded = true;

        // this is for playing the audio when opening stats
        // should be a separate method ideally but it works so im not gonna touch it
        statsOpened = LoadSound("src/assets/sounds/sfx/statsOpened.mp3");
        PlaySound(statsOpened);
        UnloadSound(statsOpened);
    }
}

Statistics::Statistics(GameState& gameState, DataBase& dataBase)
        : State(gameState)
        , dataBase(dataBase)
        , statsLoaded(false)
        {
            stateChangedSFX = LoadSound("src/assets/sounds/sfx/stateChanged.mp3");
        }
Statistics::~Statistics(){
    UnloadSound(stateChangedSFX);
}

void Statistics::draw(){
    auto posY { initPosY };  

    // header
    drawHeader(posY);

    // score
    drawScore(posY);

    // enemies
    drawEnemiesDefeated(posY);

    // waves
    drawWavesReached(posY);

    // time
    drawTimePlayed(posY);

    // exit hint matches settings style
    DrawText("Press ENTER to go back", GetScreenWidth() - MeasureText("Press ENTER to go back", textSize) - 23, GetScreenHeight() - 40, textSize, GOLD);

    // making a dark black rectangular overlay over screen if no stats there
    if (!statsLoaded || !stats.totalTimePlayed)
        drawOverLay();
}
void Statistics::update(){
    loadStats();

    if (IsKeyPressed(KEY_ENTER)){
        statsLoaded = false;
        PlaySound(stateChangedSFX);

        gameState   = MENU;
    }
} 