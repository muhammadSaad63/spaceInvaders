#pragma once


#include <vector>
#include <string>
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

// class DataBase{
//     private:
//         inline static SQLite::Database* db {nullptr};              

//         // internal, helper methods
//         static void createTable_players();
//         static void createTable_games();
//         static void initTable_players();
//         static void upperCaseStr(string& playerName);
//         static int  getNumUniquePlayersInGames();
//         static int  getTotalGames();

//         // default constructor
//         DataBase() {}                                       // so no object can be made

//     public:
//         // init method instead of constructor (since no objects are to be made)
//         static void init();

//         // writing/adding data
//         static void addPlayer(string& playerName);
//         static void addGame(GameData& gameData);

//         // fetching/reading data
//         static vector<GameData> getHistory(int numEntries);
//         static vector<GameData> getLeaderBoards(int numEntries);
// };

class DataBase{
    private:
        SQLite::Database db;              

        // internal, helper methods
        void createTable_players();
        void createTable_games();
        void initTable_players();
        void upperCaseStr(string& playerName);
        int  getNumUniquePlayersInGames();
        int  getTotalGames();

    public:
        DataBase();

        // writing/adding data
        void addPlayer(string& playerName);
        void addGame(GameData& gameData);
        
        // fetching/reading data
        vector<GameData> getHistory(int numEntries);
        vector<GameData> getLeaderBoards(int numEntries);
};