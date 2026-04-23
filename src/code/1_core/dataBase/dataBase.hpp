#pragma once


#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>
using std::vector;


struct GameData{
    int   gameID;

    // int    playerID;
    // string playerName;

    int   score;
    int   enemiesDefeated;
    int   waveReached;

    // string timeStarted;
    // string timeEnded;
    double timePlayed;
};
struct StatData{
    // Score Statistics
    int totalScore;
    int maxScorePerGame;
    int avgScorePerGame;

    // Enemy Statistics
    int totalEnemiesDefeated;
    int maxEnemiesDefeatedPerGame;
    int avgEnemiesDefeatedPerGame;

    // Wave Statistics
    int totalWavesCleared;
    int maxWavesClearedPerGame;
    int avgWavesClearedPerGame;

    // Time Statistics
    double totalTimePlayed;
    double maxTimePlayedPerGame;
    double avgTimePlayedPerGame;
};

class DataBase{
    private:
        SQLite::Database db;              

        // internal, helper methods
        // void createTable_players();
        void createTable_games();
        // void initTable_players();
        // void upperCaseStr(string& playerName);
        // int  getNumUniquePlayersInGames();
        int  getTotalGames();

    public:
        DataBase();

        // writing/adding data
        // void addPlayer(string& playerName);
        void addGame(GameData& gameData);
        
        // fetching/reading data
        vector<GameData> getHistory(int numEntries);
        // vector<GameData> getLeaderBoards(int numEntries);
        StatData         getStatistics();
};