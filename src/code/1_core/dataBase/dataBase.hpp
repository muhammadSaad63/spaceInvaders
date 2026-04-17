#pragma once


#include <vector>
#include <string>
#include <sqlite3.h>
#include "dataBase.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
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
        static SQLite::Database db("space.db",);

        // internal, helper methods
        static void createTable_players();
        static void createTable_games();
        static void initTable_players();
        static void upperCaseStr(string& playerName);
        static int  getNumUniquePlayersInGames();
        static int  getTotalGames();

        // default constructor
        DataBase() {}                                       // so no object can be made

    public:
        // init method instead of constructor
        static void init();

        // writing/adding data
        static void addPlayer(string& playerName);
        static void addGame(GameData& gameData);
        
        // fetching/reading data
        static vector<GameData> getHistory(int numEntries);
        static vector<GameData> getLeaderBoards(int numEntries);
};