#include <raylib.h>
#include "statistics.hpp"


void Statistics::loadStats(){
    if (!statsLoaded){
        stats       = dataBase.getStatistics();
        statsLoaded = true;
    }
}

Statistics::Statistics(GameState& gameState, DataBase& dataBase)
        : State(gameState)
        , dataBase(dataBase)
        , statsLoaded(false)
        {}

void Statistics::draw(){
    int posY = initPosY;  

    // header
    DrawText("Statistics", posX, posY, textSize + 10, GOLD);
    posY += (textSize + 10) + 15;
    DrawLineEx({(float)posX, (float)posY}, {(float)GetScreenWidth() - posX, (float)posY}, 1, DARKGRAY);
    posY += 20;

    // score
    {
        DrawText("— SCORE",                               posX, posY, textSize, GOLD);
        posY += textSize + 5;

        DrawText("Total Score",                           posX, posY, textSize, RAYWHITE);
        DrawText(TextFormat("%d", stats.totalScore),      posX + offset, posY, textSize, YELLOW);
        posY += textSize + 5;

        DrawText("Best Score",                            posX, posY, textSize, RAYWHITE);
        DrawText(TextFormat("%d", stats.maxScorePerGame), posX + offset, posY, textSize, YELLOW);
        posY += textSize + 5;

        DrawText("Avg Score / Game",                      posX, posY, textSize, RAYWHITE);
        DrawText(TextFormat("%d", stats.avgScorePerGame), posX + offset, posY, textSize, YELLOW);
        posY += textSize + 20;
    }

    // enemies
    DrawText("— Enemies",                                  posX, posY, textSize, GOLD);
    posY += textSize + 5;
    DrawText("Total Defeated",                             posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.totalEnemiesDefeated), posX + offset, posY, textSize, RED);
    posY += textSize + 5;
    DrawText("Most In One Game",                           posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.maxEnemiesDefeatedPerGame), posX + offset, posY, textSize, RED);
    posY += textSize + 5;
    DrawText("Avg Defeated / Game",                        posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.avgEnemiesDefeatedPerGame), posX + offset, posY, textSize, RED);
    posY += textSize + 20;

    // waves
    DrawText("— Waves",                                    posX, posY, textSize, GOLD);
    posY += textSize + 5;
    DrawText("Total Waves Cleared",                        posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.totalWavesCleared),    posX + offset, posY, textSize, SKYBLUE);
    posY += textSize + 5;
    DrawText("Best Wave Reached",                          posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.maxWavesClearedPerGame), posX + offset, posY, textSize, SKYBLUE);
    posY += textSize + 5;
    DrawText("Avg Wave / Game",                            posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%d", stats.avgWavesClearedPerGame), posX + offset, posY, textSize, SKYBLUE);
    posY += textSize + 20;

    // time
    DrawText("— Time",                                     posX, posY, textSize, GOLD);
    posY += textSize + 5;
    DrawText("Total Time Played",                          posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%dm %ds", stats.totalTimePlayed / 60, stats.totalTimePlayed % 60),
                                                           posX + offset, posY, textSize, LIME);
    posY += textSize + 5;
    DrawText("Longest Game",                               posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%dm %ds", stats.maxTimePlayedPerGame / 60, stats.maxTimePlayedPerGame % 60),
                                                           posX + offset, posY, textSize, LIME);
    posY += textSize + 5;
    DrawText("Avg Time / Game",                            posX, posY, textSize, RAYWHITE);
    DrawText(TextFormat("%dm %ds", stats.avgTimePlayedPerGame / 60, stats.avgTimePlayedPerGame % 60),
                                                           posX + offset, posY, textSize, LIME);
    posY += textSize + 25;

    DrawLineEx({(float)posX, (float)posY}, {(float)GetScreenWidth() - posX, (float)posY}, 1, DARKGRAY);
    posY += 15;

    // exit hint — matches settings style
    DrawText("   > Press ENTER to go back", posX, posY, textSize, DARKGRAY);

    // empty state
    if (!statsLoaded || stats.totalScore == 0){
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.7f));
        DrawText("No games played yet  :(",
                 GetScreenWidth()/2  - MeasureText("No games played yet  :(", 40)/2,
                 GetScreenHeight()/2 - 20, 40, DARKGRAY);
    }
}

void Statistics::update(){
    loadStats();

    if (IsKeyPressed(KEY_ENTER)){
        statsLoaded = false;
        gameState   = MENU;
    }
} 