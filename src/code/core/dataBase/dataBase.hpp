#pragma once


#include <string>


struct GameData{
    int    gameID;

    int    playerID;
    string playerName;

    int    score;
    int    enemiesDefeated;
    int    waveReached;

    string timeStarted;
    string timeEnded;
    int    timePlayed;
};