#pragma once


#include <cctype>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <SQLiteCpp.h>
#include "dataBase.hpp"
using std::string, std::vector;


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

class DataBase{
    private:
        SQLite::Database db;

        void createTable_players();
        void createTable_games();
        void initTable_players();
        void upperCaseStr(string& playerName);
        int getNumUniquePlayersInGames();
        int getTotalGames();

    public:
        DataBase();

        // writing/adding data
        void addPlayer(string& playerName);
        void addGame(GameData& gameData);
        
        // fetching/reading data
        vector<GameData> getHistory(int numEntries);
        vector<GameData> getLeaderBoards(int numEntries);
};